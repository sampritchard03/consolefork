#include "stdafx.h"
#include "com.mojang.nbt.h"
#include "net.minecraft.stats.h"
#include "net.minecraft.world.level.tile.h"
#include "net.minecraft.world.phys.h"
#include "net.minecraft.world.level.h"
#include "net.minecraft.world.item.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.entity.ai.attributes.h"
#include "net.minecraft.world.entity.ai.goal.h"
#include "net.minecraft.world.entity.ai.navigation.h"
#include "net.minecraft.world.damagesource.h"
#include "net.minecraft.world.entity.item.h"
#include "net.minecraft.world.entity.monster.h"
#include "net.minecraft.world.entity.player.h"
#include "net.minecraft.world.entity.global.h"
#include "Lizard.h"
#include "..\Minecraft.Client\Textures.h"
#include "MobCategory.h"



Lizard::Lizard(Level *level) : Animal( level )
{
	// 4J Stu - This function call had to be moved here from the Entity ctor to ensure that
	// the derived version of the function is called
	this->defineSynchedData();
	registerAttributes();
	setHealth(getMaxHealth());

	shedTime = random->nextInt(20 * 60 * 5) + 20 * 60 * 2;
	tailTime = 0;
	hasDropped = false;

	setSize(0.8F, 0.4F);

	getNavigation()->setAvoidWater(true);
	goalSelector.addGoal(0, new FloatGoal(this));
	goalSelector.addGoal(1, new PanicGoal(this, 2.0));
	goalSelector.addGoal(3, new BreedGoal(this, 1.0));
	goalSelector.addGoal(4, new TemptGoal(this, 1.2, Item::carrots_Id, false));
	goalSelector.addGoal(5, new FollowParentGoal(this, 1.1));
	goalSelector.addGoal(6, new RandomStrollGoal(this, 1.0));
	goalSelector.addGoal(7, new LookAtPlayerGoal(this, typeid(Player), 6));
	goalSelector.addGoal(8, new RandomLookAroundGoal(this));
}

bool Lizard::canSpawn() {
	int xt = Mth::floor(x);
	int yt = Mth::floor(bb->y0);
	int zt = Mth::floor(z);
	return level->getTile(xt, yt - 1, zt) == Tile::sand_Id && level->getDaytimeRawBrightness(xt, yt, zt) > 8 && AgableMob::canSpawn();
}

bool Lizard::hurt(DamageSource *dmgSource, float dmg)
{
	if (dynamic_cast<EntityDamageSource *>(dmgSource) != NULL && dropTail(dynamic_pointer_cast<LivingEntity>(dmgSource->getDirectEntity()))) dmg -= 2;
	if (dmg <= 0) return false;

	return Animal::hurt(dmgSource, dmg);
}

bool Lizard::dropTail(shared_ptr<LivingEntity> attacker) {
	if (hasTail()) {
		if (level->isClientSide || hasDropped) return true; // hasDropped exists because sometimes hurt() is called more than once when you hit something.

		if (isOnFire()) spawnAtLocation(Item::porkChop_cooked_Id, 1);
		else spawnAtLocation(Item::lizardTail_Id, 1);
		playSound( eSoundType_MOB_CHICKENPLOP, 1.0f, (random->nextFloat() - random->nextFloat()) * 0.2f + 1.0f);
		tailTime = random->nextInt(20 * 60 * 5) + 20 * 60 * 5;
		hasDropped = true;
		setLastHurtByMob(attacker);

		return true;
	} else return false;
}

bool Lizard::useNewAi()
{
	return true;
}

void Lizard::registerAttributes()
{
	Animal::registerAttributes();

	getAttribute(SharedMonsterAttributes::MAX_HEALTH)->setBaseValue(10);
	getAttribute(SharedMonsterAttributes::MOVEMENT_SPEED)->setBaseValue(0.25f);
}

void Lizard::tick()
{
	Animal::tick();

	if (!level->isClientSide) {
		setTail(tailTime <= 0);
		if (!hasTail()) {
			tailTime--;
		}
		hasDropped = false;
		if (--shedTime <= 0) {
			playSound( eSoundType_MOB_CHICKENPLOP, 1.0f, (random->nextFloat() - random->nextFloat()) * 0.2f + 1.0f);
			spawnAtLocation(Item::egg->id, 1);
			shedTime = random->nextInt(20 * 60 * 5) + 20 * 60 * 2;
		}
	}
}

void Lizard::defineSynchedData() 
{
	Animal::defineSynchedData();
	entityData->define(DATA_TAIL_ID, (byte) 0);
}

void Lizard::addAdditonalSaveData(CompoundTag *tag) 
{
	Animal::addAdditonalSaveData(tag);
	tag->putInt(L"ShedTime", shedTime);
	tag->putInt(L"TailTime", tailTime);
}

void Lizard::readAdditionalSaveData(CompoundTag *tag) 
{
	Animal::readAdditionalSaveData(tag);
	shedTime = tag->getInt(L"ShedTime");
	tailTime = tag->getInt(L"TailTime");
}

int Lizard::getHurtSound() 
{
	return eSoundType_MOB_PIG_AMBIENT;
}

int Lizard::getDeathSound() 
{
	return eSoundType_MOB_PIG_DEATH;
}

void Lizard::playStepSound(int xt, int yt, int zt, int t)
{
	playSound(eSoundType_MOB_PIG_STEP, 0.15f, 1);
}

void Lizard::dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel)
{
	dropTail(nullptr);
}

bool Lizard::hasTail() 
{
	return (entityData->getByte(DATA_TAIL_ID) & 1) != 0;
}

void Lizard::setTail(bool value) 
{
	if (value) 
	{
		entityData->set(DATA_TAIL_ID, (byte) 1);
	} 
	else 
	{
		entityData->set(DATA_TAIL_ID, (byte) 0);
	}
}

shared_ptr<AgableMob> Lizard::getBreedOffspring(shared_ptr<AgableMob> target)
{
	// 4J - added limit to number of animals that can be bred
	if( level->canCreateMore( GetType(), Level::eSpawnType_Breed) )
	{
		return shared_ptr<Lizard>( new Lizard(level) );
	}
	else
	{
		return nullptr;
	}
}

bool Lizard::isFood(shared_ptr<ItemInstance> itemInstance)
{
	return itemInstance != NULL && itemInstance->id == Item::carrots_Id;
}

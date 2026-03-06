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

	setSize(0.9f, 0.9f);

	getNavigation()->setAvoidWater(true);
	goalSelector.addGoal(0, new FloatGoal(this));
	goalSelector.addGoal(1, new PanicGoal(this, 1.25));
	goalSelector.addGoal(3, new BreedGoal(this, 1.0));
	goalSelector.addGoal(4, new TemptGoal(this, 1.2, Item::carrotOnAStick_Id, false));
	goalSelector.addGoal(4, new TemptGoal(this, 1.2, Item::carrots_Id, false));
	goalSelector.addGoal(5, new FollowParentGoal(this, 1.1));
	goalSelector.addGoal(6, new RandomStrollGoal(this, 1.0));
	goalSelector.addGoal(7, new LookAtPlayerGoal(this, typeid(Player), 6));
	goalSelector.addGoal(8, new RandomLookAroundGoal(this));
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

void Lizard::newServerAiStep()
{
	Animal::newServerAiStep();
}

void Lizard::defineSynchedData() 
{
	Animal::defineSynchedData();
	entityData->define(DATA_TAIL_ID, (byte) 0);
}

void Lizard::addAdditonalSaveData(CompoundTag *tag) 
{
	Animal::addAdditonalSaveData(tag);
	tag->putBoolean(L"Tail", hasTail());
}

void Lizard::readAdditionalSaveData(CompoundTag *tag) 
{
	Animal::readAdditionalSaveData(tag);
	setTail(tag->getBoolean(L"Tail"));
}

int Lizard::getAmbientSound() 
{
	return eSoundType_MOB_PIG_AMBIENT;
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

int Lizard::getDeathLoot() 
{
	if (this->isOnFire() ) return Item::porkChop_cooked->id;
	return Item::porkChop_raw_Id;
}

void Lizard::dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel)
{
	int count = random->nextInt(3) + 1 + random->nextInt(1 + playerBonusLevel);

	for (int i = 0; i < count; i++)
	{
		spawnAtLocation(Lizard::getDeathLoot(), 1);
	}
	if (hasTail()) spawnAtLocation(Item::saddle_Id, 1);
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

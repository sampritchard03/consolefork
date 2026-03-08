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
#include "Bird.h"
#include "..\Minecraft.Client\Textures.h"
#include "Tile.h"
#include "MobCategory.h"
#include "PanicBirdGoal.h"


Bird::Bird(Level *level) : Animal( level )
{
	// 4J Stu - This function call had to be moved here from the Entity ctor to ensure that
	// the derived version of the function is called
	this->defineSynchedData();
	registerAttributes();
	setHealth(getMaxHealth());

	setSize(0.5F, 0.5F);

	getNavigation()->setAvoidWater(true);
	goalSelector.addGoal(0, new FloatGoal(this));
	panicGoal = new PanicBirdGoal(this);
	goalSelector.addGoal(1, panicGoal);
	goalSelector.addGoal(2, new BreedGoal(this, 1.0));
	goalSelector.addGoal(3, new TemptGoal(this, 1.2, Item::seeds_wheat_Id, false));
	goalSelector.addGoal(4, new FollowParentGoal(this, 1.1));

	goalSelector.addGoal(6, new RandomStrollGoal(this, 1.0));
	goalSelector.addGoal(7, new LookAtPlayerGoal(this, typeid(Player), 6));
	goalSelector.addGoal(8, new RandomLookAroundGoal(this));
}

int Bird::getGroundHeight() {
	int x = (int)x;
	int y = (int)y;
	int z = (int)z;

	while(y > 0) {
		int id = level->getTile(x, y, z);
		if (id != 0 && Tile::tiles[id] != nullptr) {
			Tile *tile = Tile::tiles[id];
			if (tile->isCubeShaped() && tile->material != Material::leaves) {
				return y + 1;
			}
		}
		y--;
	}

	return y + 1;
}

bool Bird::useNewAi()
{
	return true;
}

void Bird::tick() {
	Animal::tick();
	if (!this->getNavigation()->isDone() && this->onGround) {
		this->yd=.2;
	}
}


void Bird::registerAttributes()
{
	Animal::registerAttributes();

	getAttribute(SharedMonsterAttributes::MAX_HEALTH)->setBaseValue(5);
	getAttribute(SharedMonsterAttributes::MOVEMENT_SPEED)->setBaseValue(0.3f);
}

void Bird::defineSynchedData() 
{
	Animal::defineSynchedData();
	entityData->define(DATA_STATE, (byte) IDLE);
}

int Bird::birdState() {
	return entityData->getByte(DATA_STATE);
}

void Bird::setBirdState(int birdState) {
	entityData->set(DATA_STATE, (byte) birdState);
}

void Bird::addAdditonalSaveData(CompoundTag *tag) 
{
	Animal::addAdditonalSaveData(tag);
}

void Bird::readAdditionalSaveData(CompoundTag *tag) 
{
	Animal::readAdditionalSaveData(tag);
}

int Bird::getAmbientSound() 
{
	return eSoundType_MOB_PIG_AMBIENT;
}

int Bird::getHurtSound() 
{
	return eSoundType_MOB_PIG_AMBIENT;
}

int Bird::getDeathSound() 
{
	return eSoundType_MOB_PIG_DEATH;
}

void Bird::playStepSound(int xt, int yt, int zt, int t)
{
	playSound(eSoundType_MOB_PIG_STEP, 0.15f, 1);
}

void Bird::dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel)
{
	spawnAtLocation(Item::feather_Id, 1);
}

shared_ptr<AgableMob> Bird::getBreedOffspring(shared_ptr<AgableMob> target)
{
	// 4J - added limit to number of animals that can be bred
	if( level->canCreateMore( GetType(), Level::eSpawnType_Breed) )
	{
		return shared_ptr<Bird>( new Bird(level) );
	}
	else
	{
		return nullptr;
	}
}

bool Bird::isFood(shared_ptr<ItemInstance> itemInstance)
{
	return itemInstance != NULL && itemInstance->id == Item::seeds_wheat_Id;
}

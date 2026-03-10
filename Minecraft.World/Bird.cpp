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
#include "RandomStrollBirdGoal.h"
#include "FlyingBirdGoal.h"


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
	goalSelector.addGoal(2, new FlyingBirdGoal(this));
	goalSelector.addGoal(3, new BreedGoal(this, 1.0));
	goalSelector.addGoal(4, new TemptGoal(this, 1.2, Item::seeds_wheat_Id, false));
	goalSelector.addGoal(5, new FollowParentGoal(this, 1.1));
	goalSelector.addGoal(6, new RandomStrollBirdGoal(this, 1.0));
	goalSelector.addGoal(7, new LookAtPlayerGoal(this, typeid(Player), 6));
	goalSelector.addGoal(8, new RandomLookAroundGoal(this));
}

void Bird::causeFallDamage(float distance) {
}

void Bird::startFlying(bool withFlock)
{
	if (!level->isClientSide && birdState() != Bird::FLYING) {
		setBirdState(Bird::FLYING);
		flightTime = 0;
		groundY = getGroundHeight();
		
		if (withFlock) {
			std::vector<std::shared_ptr<Entity>> nearbyBirds = *level->getEntitiesOfClass(typeid(Bird), bb->grow(12, 12, 12));

			for (auto& entity : nearbyBirds)
			{
				std::shared_ptr<Bird> bird = std::dynamic_pointer_cast<Bird>(entity);
				if (bird)
				{
					bird.get()->startFlying(true);
				}
			}
		}
	}
}

int Bird::getGroundHeight() {
	int x = (int)this->x;
	int y = (int)this->y;
	int z = (int)this->z;

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

bool Bird::hurt(DamageSource *source, float dmg) {
	startFlying(true);               
	return Animal::hurt(source, dmg);
}

bool Bird::useNewAi()
{
	return true;
}

void Bird::tick() {
	Animal::tick();
	if (!this->getNavigation()->isDone()) {
		if (this->onGround) this->yd = .2;
	}
	if (birdState() != FLYING) {
		if (isStandingOnLeaves() || !this->level->isDay()) setBirdState(PERCHED);
		else setBirdState(IDLE);
	}
	flightTime++;
}

bool Bird::isStandingOnLeaves() {
	return false;
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

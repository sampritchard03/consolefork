#pragma once
#include "Animal.h"

class Player;

class Bird : public Animal
{
public:
	eINSTANCEOF GetType() { return eTYPE_BIRD; }
	static Entity *create(Level *level) { return new Bird(level); }
	static const enum eBirdStates {
		IDLE,
		FLYING,
		PERCHED
	};
	int flightTime;
	int groundY;
private:
	static const int DATA_STATE = 16;

public:
	Bird(Level *level);
	virtual bool useNewAi();
	virtual void tick();
	virtual void startFlying(bool withFlock);

protected:
	virtual void registerAttributes();

protected:
	virtual void defineSynchedData();

public:
	virtual bool isStandingOnLeaves();
	virtual int getGroundHeight();
	virtual int birdState();
	virtual void setBirdState(int birdState);
	virtual void addAdditonalSaveData(CompoundTag *tag);
	virtual void readAdditionalSaveData(CompoundTag *tag);
	virtual void causeFallDamage(float distance);
	virtual bool hurt(DamageSource *source, float dmg);

protected:
	virtual int getAmbientSound();
	virtual int getHurtSound();
	virtual int getDeathSound();
	virtual void playStepSound(int xt, int yt, int zt, int t);

protected:
	virtual void dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel);

public:
	virtual shared_ptr<AgableMob> getBreedOffspring(shared_ptr<AgableMob> target);
	bool isFood(shared_ptr<ItemInstance> itemInstance);
};



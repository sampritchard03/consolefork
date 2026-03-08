#pragma once
#include "Animal.h"

class Player;
class PanicBirdGoal;

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
	PanicBirdGoal *panicGoal;
	int flightTime;
	int groundY;
private:
	static const int DATA_STATE = 16;

public:
	Bird(Level *level);
	virtual bool useNewAi();
	virtual void tick();

protected:
	virtual void registerAttributes();

protected:
	virtual void defineSynchedData();

public:
	virtual int getGroundHeight();
	virtual int birdState();
	virtual void setBirdState(int birdState);
	virtual void addAdditonalSaveData(CompoundTag *tag);
	virtual void readAdditionalSaveData(CompoundTag *tag);

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



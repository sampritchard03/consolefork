#pragma once
#include "Animal.h"

class Player;
class ControlledByPlayerGoal;

class Lizard : public Animal
{
public:
	eINSTANCEOF GetType() { return eTYPE_LIZARD; }
	static Entity *create(Level *level) { return new Lizard(level); }
private:
	static const int DATA_TAIL_ID = 16;

public:
	Lizard(Level *level);

	virtual bool useNewAi();

protected:
	virtual void registerAttributes();
	virtual void newServerAiStep();

protected:
	virtual void defineSynchedData();

public:
	virtual void addAdditonalSaveData(CompoundTag *tag);
	virtual void readAdditionalSaveData(CompoundTag *tag);

protected:
	virtual int getAmbientSound();
	virtual int getHurtSound();
	virtual int getDeathSound();
	virtual void playStepSound(int xt, int yt, int zt, int t);

protected:
	virtual int getDeathLoot();
	virtual void dropDeathLoot(bool wasKilledByPlayer, int playerBonusLevel);

public:
	bool hasTail();
	void setTail(bool value);

public:
	virtual shared_ptr<AgableMob> getBreedOffspring(shared_ptr<AgableMob> target);
	bool isFood(shared_ptr<ItemInstance> itemInstance);
};



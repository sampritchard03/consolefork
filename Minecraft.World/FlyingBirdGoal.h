#pragma once

#include "Goal.h"

class Bird;
class Vec3;

class FlyingBirdGoal : public Goal
{
private:
	Bird *mob;
	Vec3 *landingPos = NULL;

public:
	FlyingBirdGoal(Bird *mob);

	virtual bool canUse();
	virtual void stop();
	virtual void tick();
	virtual void landingTick();
	virtual void flockingTick();
	virtual void findSafeLandingSpot(bool shouldLandOnLeavesOnly);
	virtual int findLandingHeightAt(int bx, int bz, bool shouldLandOnLeavesOnly);
};

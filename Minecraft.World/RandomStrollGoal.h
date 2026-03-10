#pragma once

#include "Goal.h"

class PathfinderMob;

class RandomStrollGoal : public Goal
{
protected:
	PathfinderMob *mob;
private:
	double wantedX, wantedY, wantedZ;
	double speedModifier;

public:
	RandomStrollGoal(PathfinderMob *mob, double speedModifier);

	virtual bool canUse();
	virtual bool canContinueToUse();
	virtual void start();
	virtual void stop();
};
#pragma once

#include "RandomStrollGoal.h"

class Bird;

class RandomStrollBirdGoal : public RandomStrollGoal
{
private:
	Bird *bird;
public:
	RandomStrollBirdGoal(Bird *bird, double speedModifier);

	virtual bool isIdle();
	virtual bool canUse();
	virtual bool canContinueToUse();

};

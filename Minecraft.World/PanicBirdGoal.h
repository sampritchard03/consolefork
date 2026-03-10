#pragma once

#include "Goal.h"
#include <random>

class Bird;

class PanicBirdGoal : public Goal
{
private:
	Bird *mob;

public:
	PanicBirdGoal(Bird *mob);

	virtual bool canUse();
	virtual void start();
	virtual bool canContinueToUse();
};
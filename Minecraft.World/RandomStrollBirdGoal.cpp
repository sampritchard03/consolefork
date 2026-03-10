#include "stdafx.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.entity.ai.control.h"
#include "net.minecraft.world.entity.ai.navigation.h"
#include "net.minecraft.world.entity.ai.util.h"
#include "net.minecraft.world.phys.h"
#include "SharedConstants.h"
#include "RandomStrollBirdGoal.h"
#include "Bird.h"

RandomStrollBirdGoal::RandomStrollBirdGoal(Bird *bird, double speedModifier) : RandomStrollGoal(bird, speedModifier)
{
	this->bird = bird;
}

bool RandomStrollBirdGoal::isIdle()
{	
	if(bird->birdState() == Bird::IDLE) return true;
	else return false;
}

bool RandomStrollBirdGoal::canUse() {
	if (!isIdle()) return false;
	else return RandomStrollGoal::canUse();
}

bool RandomStrollBirdGoal::canContinueToUse() {
	if (!isIdle()) return false;
	else return RandomStrollGoal::canContinueToUse();
}
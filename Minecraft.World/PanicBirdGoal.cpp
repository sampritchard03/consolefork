#include "stdafx.h"
#include "net.minecraft.world.entity.ai.control.h"
#include "net.minecraft.world.entity.ai.navigation.h"
#include "net.minecraft.world.entity.ai.util.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.phys.h"
#include "PanicBirdGoal.h"
#include "Bird.h"
#include "Level.h"

PanicBirdGoal::PanicBirdGoal(Bird *mob)
{
	this->mob = mob;
    //Goal::setRequiredControlFlags(Control::MoveControlFlag);
}

bool PanicBirdGoal::canUse()
{
	if (mob->getLastHurtByMob() == nullptr && !mob->isOnFire()) return false;

	return true;
}

void PanicBirdGoal::start() {
	mob->startFlying(false);
}

bool PanicBirdGoal::canContinueToUse()
{
	return false;
}
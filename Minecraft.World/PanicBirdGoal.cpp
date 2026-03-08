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
    Goal::setRequiredControlFlags(Control::MoveControlFlag);
}

bool PanicBirdGoal::canUse()
{
	if (mob->getLastHurtByMob() == nullptr && !mob->isOnFire()) return false;
	const int hurtTimeout = mob->getLastHurtByMobTimestamp();
	if (hurtTimeout == 0) return false;
    static thread_local std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(60, 100);
	const int panicDuration = dist(rng);
	if (mob->tickCount - hurtTimeout > panicDuration) return false;

	return true;
}

void PanicBirdGoal::alertFlockToFlee() {
	std::vector<std::shared_ptr<Entity>> nearbyBirds = *mob->level->getEntitiesOfClass(typeid(*mob), mob->bb->grow(12, 12, 12));

    for (auto& entity : nearbyBirds)
    {
		std::shared_ptr<Bird> bird = std::dynamic_pointer_cast<Bird>(entity);
        if (bird)
        {
            bird.get()->panicGoal->panic();
        }
    }
}

void PanicBirdGoal::start() {
	panic();
}

void PanicBirdGoal::panic()
{

	if (mob->birdState() != Bird::FLYING) {
		mob->setBirdState(Bird::FLYING);
		mob->flightTime = 0;
		mob->groundY = mob->getGroundHeight();
		alertFlockToFlee();
	}
}

bool PanicBirdGoal::canContinueToUse()
{
	if (mob->getLastHurtByMob() == nullptr && !mob->isOnFire()) return false;
	return !mob->getNavigation()->isDone();
}
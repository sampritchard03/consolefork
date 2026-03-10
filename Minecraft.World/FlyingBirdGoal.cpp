#include "stdafx.h"
#include "net.minecraft.world.entity.h"
#include "net.minecraft.world.entity.ai.control.h"
#include "net.minecraft.world.entity.ai.navigation.h"
#include "FlyingBirdGoal.h"
#include "Bird.h"
#include "Level.h"
#include "Tile.h"

FlyingBirdGoal::FlyingBirdGoal(Bird *mob)
{
	this->mob = mob;
	//setRequiredControlFlags(Control::MoveControlFlag & Control::JumpControlFlag & Control::LookControlFlag);
}

bool FlyingBirdGoal::canUse()
{
	return mob->birdState() == Bird::FLYING;
}

void FlyingBirdGoal::stop() {
	landingPos = NULL;
}

void FlyingBirdGoal::tick()
{
	if (mob->flightTime > 20 && landingPos == NULL) {
		findSafeLandingSpot(mob->flightTime <= 40);
	}

	if (landingPos != NULL) {
		landingTick();
		return;
	}

	flockingTick();
}

void FlyingBirdGoal::flockingTick() {
	mob->yd += 0.1;
}

void FlyingBirdGoal::landingTick() {
	if (!mob->level->isClientSide) mob->setBirdState(Bird::IDLE);
}

void FlyingBirdGoal::findSafeLandingSpot(bool shouldLandOnLeavesOnly) {
	int bx = (int)mob->x;
	int bz = (int)mob->z;

	int offsets[][2] = { {0, 0},
		{1, 0}, {-1, 0}, {0, 1}, {0, -1},
		{1, 1}, {-1, -1}, {1, -1}, {-1, 1},
		{2, 0}, {-2, 0}, {0, 2}, {0, -2}
	};

	for (auto& offset : offsets) {
		int landingY = findLandingHeightAt(bx + offset[0], bz + offset[1], shouldLandOnLeavesOnly);
		if (landingY != -1) {
			landingPos = Vec3::newTemp(bx + offset[0], landingY, bz + offset[1]);
			return;
		}
	}
}

int FlyingBirdGoal::findLandingHeightAt(int bx, int bz, bool shouldLandOnLeavesOnly) {
	for (int by = (int)mob->y-1; by >= 0; by--) {
		int id = mob->level->getTile(bx, by, bz);
		if (id != 0) {
			Tile *tile = Tile::tiles[id];
			if (!shouldLandOnLeavesOnly && tile->isCubeShaped() || tile->material == Material::leaves) {
				return by + 1;
			}
		}
	}
	return -1;
}
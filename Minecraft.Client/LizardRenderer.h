#pragma once
#include "MobRenderer.h"

class LizardRenderer : public MobRenderer
{
private:
	static ResourceLocation LIZARD_LOCATION;

public:
	LizardRenderer();

public:
	virtual void render(shared_ptr<Entity> mob, double x, double y, double z, float rot, float a);
	virtual ResourceLocation *getTextureLocation(shared_ptr<Entity> mob);
};
#pragma once
#include "MobRenderer.h"

class BirdRenderer : public MobRenderer
{
private:
	static ResourceLocation BIRD_LOCATION;

public:
	BirdRenderer();

public:
	virtual void render(shared_ptr<Entity> mob, double x, double y, double z, float rot, float a);
	virtual ResourceLocation *getTextureLocation(shared_ptr<Entity> mob);
};
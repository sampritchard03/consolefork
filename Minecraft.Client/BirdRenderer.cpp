#include "stdafx.h"
#include "BirdRenderer.h"
#include "..\Minecraft.World\net.minecraft.world.entity.animal.h"
#include "BirdModel.h"

ResourceLocation BirdRenderer::BIRD_LOCATION = ResourceLocation(TN_MOB_BIRD);

BirdRenderer::BirdRenderer() : MobRenderer(new BirdModel(),0.4F)
{
}

void BirdRenderer::render(shared_ptr<Entity> mob, double x, double y, double z, float rot, float a)
{
	MobRenderer::render(mob, x, y, z, rot, a);
} 

ResourceLocation *BirdRenderer::getTextureLocation(shared_ptr<Entity> mob)
{
    return &BIRD_LOCATION;
}
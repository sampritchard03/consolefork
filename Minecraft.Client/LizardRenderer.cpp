#include "stdafx.h"
#include "LizardRenderer.h"
#include "..\Minecraft.World\net.minecraft.world.entity.animal.h"
#include "LizardModel.h"

ResourceLocation LizardRenderer::LIZARD_LOCATION = ResourceLocation(TN_MOB_LIZARD);

LizardRenderer::LizardRenderer() : MobRenderer(new LizardModel(),0.4F)
{
}

void LizardRenderer::render(shared_ptr<Entity> mob, double x, double y, double z, float rot, float a)
{
	MobRenderer::render(mob, x, y, z, rot, a);
} 

ResourceLocation *LizardRenderer::getTextureLocation(shared_ptr<Entity> mob)
{
    return &LIZARD_LOCATION;
}
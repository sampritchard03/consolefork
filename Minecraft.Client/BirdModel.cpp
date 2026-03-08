#include "stdafx.h"
#include "BirdModel.h"
#include "..\Minecraft.World\Mth.h"
#include "ModelPart.h"
#include "..\Minecraft.World\Bird.h"

BirdModel::BirdModel() : Model()
{
	yHeadOffs = 3;
	zHeadOffs = 0;

	texWidth = 32;
	texHeight = 16;

	float g = 0;

	body = new ModelPart(this, 0, 0);
	body->addBox(-2.0F, -2.0F, -3.0F, 4, 4, 5, g); // Head
	body->setPos(0.0F, 20.0F, 0.0F);

	beak = new ModelPart(this, 0, 13);
	beak->addBox(-0.5F, 0.0F, -3.0F, 1, 1, 2, g); // Body
	beak->setPos(0.0F, 0.0F, -2.0F);
	body->addChild(beak);

	crest = new ModelPart(this, 6, 10);
	crest->addBox(0.0F, -3.0F, -3.0F, 0, 2, 4, g); // Tail
	crest->setPos(0.0F, -1.0F, 0.0F);
	body->addChild(crest);
		
	tail = new ModelPart(this, 13, 0);
	tail->addBox(-1.0F, -0.5F, 2.0F, 2, 1, 4, g); // Leg1
	tail->setPos(0.0F, 0.5F, 0.0F);
	body->addChild(tail);

	wingLeft = new ModelPart(this, 22, 1);
	wingLeft->addBox(0.5F, 1.5F, -2.0F, 1, 3, 4, g); // Leg0
	wingLeft->setPos(1.5F, -2.5F, 0.0F);
	body->addChild(wingLeft);

	wingRight = new ModelPart(this, 22, 1);
	wingRight->addBox(-1.5F, 1.5F, -2.0F, 1, 3, 4, g); // Leg2
	wingRight->setPos(-1.5F, -2.5F, 0.0F);
	body->addChild(wingRight);

	legLeft = new ModelPart(this, 0, 0);
	legLeft->addBox(-0.5F, 1.75F, -0.25F, 1, 2, 0, g); // Leg2
	legLeft->setPos(1.0F, 0.2F, 0.25F);
	body->addChild(legLeft);

	footLeft = new ModelPart(this, -1, 2);
	footLeft->addBox(-0.5F, -0.05F, -1.25F, 1, 0, 1, g); // Leg2
	footLeft->setPos(0.0F, 3.8F, 0.0F);
	legLeft->addChild(footLeft);

	
	legRight = new ModelPart(this, 0, 0);
	legRight->addBox(-0.5F, 1.75F, -0.25F, 1, 2, 0, g); // Leg2
	legRight->setPos(-1.0F, 0.2F, 0.25F);
	body->addChild(legRight);

	footRight = new ModelPart(this, -1, 2);
	footRight->addBox(-0.5F, -0.05F, -1.25F, 1, 0, 1, g); // Leg2
	footLeft->setPos(0.0F, 3.8F, 0.0F);
	legRight->addChild(footRight);

	// 4J added - compile now to avoid random performance hit first time cubes are rendered
    body->compile(1.0f/16.0f);
	beak->compile(1.0f/16.0f);
	crest->compile(1.0f/16.0f);
	tail->compile(1.0f/16.0f);
    wingLeft->compile(1.0f/16.0f);
    wingRight->compile(1.0f/16.0f);
    legLeft->compile(1.0f/16.0f);
    footLeft->compile(1.0f/16.0f);
	legRight->compile(1.0f/16.0f);
    footRight->compile(1.0f/16.0f);
}

void BirdModel::render(shared_ptr<Entity> entity, float time, float r, float bob, float yRot, float xRot, float scale, bool usecompiled)
{
    setupAnim(time, r, bob, yRot, xRot, scale, entity);

	if (young) 
	{
		float ss = 2.0f;
		glPushMatrix();
		glScalef(1 / ss, 1 / ss, 1 / ss);
		glTranslatef(0, 24 * scale, 0);
		body->render(scale, usecompiled);
		glPopMatrix();
	} 
	else 
	{
		body->render(scale, usecompiled);
	}
}

void BirdModel::setupAnim(float time, float r, float bob, float yRot, float xRot, float scale, shared_ptr<Entity> entity, unsigned int uiBitmaskOverrideAnim)
{
	float rad = (float) (180 / PI);
	body->xRot = (xRot) / rad + (entity.get()->yd);
    body->yRot = yRot / rad;

    tail->xRot = 0.25F;

    legLeft->xRot = (Mth::cos(time * 0.6662f) * 1.4f) * r;
    legRight->xRot = (Mth::cos(time * 0.6662f + PI) * 1.4f) * r;

	// wing flap code
}

void BirdModel::render(BirdModel *model, float scale, bool usecompiled)
{
    body->yRot = model->body->yRot;
    body->xRot = model->body->xRot;

	tail->yRot = model->tail->yRot;
	tail->xRot = model->tail->xRot;

    wingLeft->xRot = model->wingLeft->xRot;
    wingRight->xRot = model->wingRight->xRot;

    legLeft->xRot = model->legLeft->xRot;
    legRight->xRot = model->legRight->xRot;

	if (young) 
	{
		float ss = 2.0f;
		glPushMatrix();
		glScalef(1 / ss, 1 / ss, 1 / ss);
		glTranslatef(0, 24 * scale, 0);
		body->render(scale, usecompiled);
		glPopMatrix();
	} 
	else 
	{
		body->render(scale, usecompiled);
	}
}

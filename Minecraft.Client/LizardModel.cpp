#include "stdafx.h"
#include "LizardModel.h"
#include "..\Minecraft.World\Mth.h"
#include "ModelPart.h"

LizardModel::LizardModel() : Model()
{
	yHeadOffs = 2;
	zHeadOffs = 3;

	float g = 0;

	head = new ModelPart(this, 0, 0);
	head->addBox(-2.0F, -3.0F, -6.0F, 4, 4, 6, g); // Head
	head->setPos(0.0F, 21.0F, -5.0F);

	body = new ModelPart(this, 1, 10);
	body->addBox(-2.0F, -2.0F, -4.0F, 4, 4, 9, g); // Body
	body->setPos(0.0F, 21.0F, -1.0F);

	tail = new ModelPart(this, 21, 0);
	tail->addBox(-2.0F, -1.5F, 0.0F, 4, 2, 9, g); // Tail
	tail->setPos(0.0F, 21.5F, 4.0F);
		
	leg1 = new ModelPart(this, 0, 26);
	leg1->addBox(-2.0F, -1.0F, -1.0F, 2, 4, 2, g); // Leg1
	leg1->setPos(-2.0F, 21.0F, -4.0F);

	leg0 = new ModelPart(this, 0, 26);
	leg0->addBox(-2.0F, -1.0F, -1.0F, 2, 4, 2, g); // Leg0
	leg0->setPos(4.0F, 21.0F, -4.0F);

	leg2 = new ModelPart(this, 0, 26);
	leg2->addBox(-2.0F, -1.0F, -1.0F, 2, 4, 2, g); // Leg2
	leg2->setPos(4.0F, 21.0F, 3.0F);

	leg3 = new ModelPart(this, 0, 26);
	leg3->addBox(-2.0F, -1.0F, -1.0F, 2, 4, 2, g); // Leg2
	leg3->setPos(-2.0F, 21.0F, 3.0F);

	// 4J added - compile now to avoid random performance hit first time cubes are rendered
	head->compile(1.0f/16.0f);
    body->compile(1.0f/16.0f);
	tail->compile(1.0f/16.0f);
    leg0->compile(1.0f/16.0f);
    leg1->compile(1.0f/16.0f);
    leg2->compile(1.0f/16.0f);
    leg3->compile(1.0f/16.0f);
}

void LizardModel::render(shared_ptr<Entity> entity, float time, float r, float bob, float yRot, float xRot, float scale, bool usecompiled)
{
    setupAnim(time, r, bob, yRot, xRot, scale, entity);

	if (young) 
	{
		float ss = 2.0f;
		glPushMatrix();
		glTranslatef(0, yHeadOffs * scale, zHeadOffs * scale);
		head->render(scale,usecompiled);
		glPopMatrix();
		glPushMatrix();
		glScalef(1 / ss, 1 / ss, 1 / ss);
		glTranslatef(0, 24 * scale, 0);
		body->render(scale, usecompiled);
		tail->render(scale, usecompiled);
		leg0->render(scale, usecompiled);
		leg1->render(scale, usecompiled);
		leg2->render(scale, usecompiled);
		leg3->render(scale, usecompiled);
		glPopMatrix();
	} 
	else 
	{
		head->render(scale, usecompiled);
		body->render(scale, usecompiled);
		tail->render(scale, usecompiled);
		leg0->render(scale, usecompiled);
		leg1->render(scale, usecompiled);
		leg2->render(scale, usecompiled);
		leg3->render(scale, usecompiled);
	}
}

void LizardModel::setupAnim(float time, float r, float bob, float yRot, float xRot, float scale, shared_ptr<Entity> entity, unsigned int uiBitmaskOverrideAnim)
{
	float rad = (float) (180 / PI);
    head->xRot = xRot / rad;
    head->yRot = yRot / rad;

    tail->yRot = (Mth::cos(time * 0.6662f) * 1.4f) * r;

    leg0->xRot = (Mth::cos(time * 0.6662f) * 1.4f) * r;
    leg1->xRot = (Mth::cos(time * 0.6662f + PI) * 1.4f) * r;
    leg2->xRot = (Mth::cos(time * 0.6662f + PI) * 1.4f) * r;
    leg3->xRot = (Mth::cos(time * 0.6662f) * 1.4f) * r;
}

void LizardModel::render(LizardModel *model, float scale, bool usecompiled)
{
    head->yRot = model->head->yRot;
    head->xRot = model->head->xRot;

    head->y = model->head->y;
    head->x = model->head->x;

    body->yRot = model->body->yRot;
    body->xRot = model->body->xRot;

	tail->yRot = model->tail->yRot;
	tail->xRot = model->tail->xRot;

    leg0->xRot = model->leg0->xRot;
    leg1->xRot = model->leg1->xRot;
    leg2->xRot = model->leg2->xRot;
    leg3->xRot = model->leg3->xRot;

	if (young) 
	{
		float ss = 2.0f;
		glPushMatrix();
		glTranslatef(0, 8 * scale, 4 * scale);
		head->render(scale,usecompiled);
		glPopMatrix();
		glPushMatrix();
		glScalef(1 / ss, 1 / ss, 1 / ss);
		glTranslatef(0, 24 * scale, 0);
		body->render(scale, usecompiled);
		tail->render(scale, usecompiled);
		leg0->render(scale, usecompiled);
		leg1->render(scale, usecompiled);
		leg2->render(scale, usecompiled);
		leg3->render(scale, usecompiled);
		glPopMatrix();
	} 
	else 
	{
		head->render(scale, usecompiled);
		body->render(scale, usecompiled);
		tail->render(scale, usecompiled);
		leg0->render(scale, usecompiled);
		leg1->render(scale, usecompiled);
		leg2->render(scale, usecompiled);
		leg3->render(scale, usecompiled);
	}
}

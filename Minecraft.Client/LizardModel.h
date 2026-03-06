#pragma once
#include "Model.h"

class LizardModel : public Model
{
public:
	ModelPart *head, *body, *leg0, *leg1, *leg2, *leg3, *tail;

	LizardModel();
	virtual void render(shared_ptr<Entity> entity, float time, float r, float bob, float yRot, float xRot, float scale, bool usecompiled);
	virtual void setupAnim(float time, float r, float bob, float yRot, float xRot, float scale, shared_ptr<Entity> entity, unsigned int uiBitmaskOverrideAnim = 0);
	void render(LizardModel *model, float scale, bool usecompiled);
};

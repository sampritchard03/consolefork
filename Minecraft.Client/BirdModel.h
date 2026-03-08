#pragma once
#include "Model.h"

class BirdModel : public Model
{
public:
	ModelPart *body, *beak, *crest, *tail, *wingLeft, *wingRight, *legLeft, *footLeft, *legRight, *footRight;

	BirdModel();
	virtual void render(shared_ptr<Entity> entity, float time, float r, float bob, float yRot, float xRot, float scale, bool usecompiled);
	virtual void setupAnim(float time, float r, float bob, float yRot, float xRot, float scale, shared_ptr<Entity> entity, unsigned int uiBitmaskOverrideAnim = 0);
	void render(BirdModel *model, float scale, bool usecompiled);
};
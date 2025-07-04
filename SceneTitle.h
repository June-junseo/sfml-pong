#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
protected:

public:
	SceneTitle();

	void Init() override;
	void Update(float dt) override;
	void Exit() override;
};


#pragma once
#include "Scene.h"
class SceneOption : public Scene
{
protected:

public:
	SceneOption();

	void Init() override;
	void Update(float dt) override;
	void Exit() override;
};


#pragma once
#include "Scene.h"
class Level2 : public Scene {

public:
	void Initialize() override;
	void Update(float deltaTime) override;
	int Render(ShaderProgram* program) override;
};
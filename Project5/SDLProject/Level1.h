#include "Scene.h"
class Level1 : public Scene {

public:
	void Initialize() override;
	void Update(float deltaTime) override;
	int Render(ShaderProgram* program) override;
};
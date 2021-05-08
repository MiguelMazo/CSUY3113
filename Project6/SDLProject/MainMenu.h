#include "Scene.h"
class MainMenu : public Scene {

public:
	void Initialize() override;
	void Update(float deltaTime) override;
	int Render(ShaderProgram* program) override;
};
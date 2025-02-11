#pragma once
#include "XephEngine/include/XephEngine.h"

enum class ShapeType
{
	Transform,
	Sphere,
	BoxWireframe,
	BoxFilled,
	Custom,
	Count
};

class GameState : public xe::AppState
{
protected:
	xe::Graphics::Camera _camera;
	xe::Graphics::DirectionalLight _directionalLight;
	xe::Graphics::StandardEffect _standardEffect;
	xe::Graphics::RenderObject _ground;
	xe::Graphics::RenderObject _ball;

	xe::Graphics::Animation _ballAnimation;
	float _animationTime = 0.f;

public:


	virtual ~GameState() {};

	void Initialize() override;
	void Terminate() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void DebugUI() override;

protected:
	void UpdateCameraControl(const float& deltaTime);
};
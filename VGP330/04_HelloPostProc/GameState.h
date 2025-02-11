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
	std::list<xe::Graphics::RenderGroup> _renderObjects;
	xe::Graphics::StandardEffect _standardEffect;
	xe::Graphics::PostProcEffect _postProcEffect;
	xe::Graphics::RenderObject _ground;
	xe::Graphics::RenderObject _screenQuad;
	xe::Graphics::RenderTarget _baseRenderTarget;
	xe::Graphics::Texture _combineTexture;


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
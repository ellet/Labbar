#pragma once
#include <Scene.h>

template<typename TDataType>
class ConstantBuffer;

class DirectionalLight;


struct LightBuffer
{
	Vector4f myDirection;
	Vector4f myColor;
};

class LightingTestScene : public Scene
{
public:
	LightingTestScene();
	~LightingTestScene();

	virtual void Render() override;


	virtual void Update(const Time & aDeltaTime) override;

private:
	std::shared_ptr<ModelInstance> myHead;
	std::unique_ptr<ConstantBuffer<LightBuffer>> myConstantBuffer;
	std::unique_ptr<DirectionalLight> myLight;
};

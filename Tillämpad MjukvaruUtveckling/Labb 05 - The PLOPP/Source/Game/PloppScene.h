#pragma once
#include <scene.h>
#include "ThreadPool/ThreadPool.h"

template<typename TDataType>
class ConstantBuffer;

class DirectionalLight;


struct LightBuffer
{
	Vector4f myDirection;
	Vector4f myColor;
};

class PloppScene : public Scene
{
public:
	PloppScene();
	~PloppScene();

	virtual void Update(const Time & aDeltaTime) override;

	virtual void Render() override;

private:
	void MakeSomeCubes();

	ThreadPool myThreadPool;

	std::shared_ptr<ModelInstance> myCube;
	std::shared_ptr<ModelInstance> myHead;
	std::shared_ptr<ModelInstance> mySkellyton;

	std::unique_ptr<ConstantBuffer<LightBuffer>> myConstantBuffer;
	std::unique_ptr<DirectionalLight> myLight;

	float myDetectionDistance;
	float myCameraSpeed;

	bool myHasLoadedCube;
	bool myHasLoadedHead;
	bool myHasLoadedSkelly;
};


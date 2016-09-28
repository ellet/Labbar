#pragma once
#include "Engine\Scene\Scene.h"

class PointLightScene :
	public Scene
{
public:
	PointLightScene();
	~PointLightScene();


	virtual void Update(const Time & aDeltaTime) override;
	virtual void Render() override;

private:
	std::vector<Vector4f> myLightPositions;
};


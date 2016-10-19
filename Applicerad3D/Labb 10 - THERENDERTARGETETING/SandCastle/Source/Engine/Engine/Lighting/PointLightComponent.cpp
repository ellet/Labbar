#include "stdafx.h"
#include "PointLightComponent.h"

namespace ENGINE_NAMESPACE
{
	void PointLightComponent::Initialize()
	{
		Engine::GetRenderer().GetModelRenderer().RegisterLightComponent(*this);
	}

	PointLightComponent::~PointLightComponent()
	{
		Engine::GetRenderer().GetModelRenderer().RemoveLightComponent(*this);
	}

	void PointLightComponent::LoadData(DataNode aProperties)
	{
		myRadius = aProperties["Radius"].GetFloat();
		myColor = Vector3f(aProperties["Color"][0].GetFloat(),
			aProperties["Color"][1].GetFloat(),
			aProperties["Color"][2].GetFloat());
	}

	Vector3f PointLightComponent::GetPosition() const
	{
		return myObject->GetTransformation().GetPosition();
	}

	float PointLightComponent::GetRadius() const
	{
		return myRadius;
	}

	Vector3f PointLightComponent::GetColor() const
	{
		return myColor;
	}
}

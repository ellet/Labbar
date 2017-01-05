#include "stdafx.h"
#include "Engine/Buffer/VertexBuffer.h"
#include "VisualEffectComponent.h"
#include "VisualEffect.h"

namespace SB
{
	VisualEffectComponent::VisualEffectComponent()
	{
		myVertexBuffer = std::make_shared<VertexBuffer<VisualEffectVertex>>(nullptr, 1, false);
		myVisualEffect = std::make_shared<VisualEffect>();
		myVisualEffect->SetEffect();
	}

	VisualEffectComponent::~VisualEffectComponent()
	{
	}

	void VisualEffectComponent::Update(const Time & aDeltaTime)
	{
		myRunTime += aDeltaTime;
	}

	void VisualEffectComponent::Render(const Camera & aCamera) const
	{
		VisualEffectVertex vertex;
		vertex.position = myObject->GetWorldPosition();
		vertex.color = Vector4f(1.f, 0.f, 0.f, 1.f);
		vertex.size = 100.f;

		Engine::GetInstance().GetRenderer().DisableDepthWrite();
		
		myVisualEffect->BindTexture();
		myVisualEffect->UpdateCBufferDataAndBind(Engine::GetDeltaTime(), myRunTime);
		myVertexBuffer->UpdateData(&vertex, 1, true);

		myVertexBuffer->Bind(0);
		myVisualEffect->Bind();

		Engine::GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		Engine::GetRenderer().GetContext()->Draw(1, 0);
		Engine::GetInstance().GetRenderer().EnableDepth();
	}

}
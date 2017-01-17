#include "stdafx.h"
#include "VisualEffect.h"

namespace SB
{
	VisualEffect::VisualEffect()
	{
		myVertexLayout = nullptr;
	}

	VisualEffect::~VisualEffect()
	{
	}

	void VisualEffect::UpdateCBufferDataAndBind(const Time & aDeltaTime, const Time & aRunTime)
	{

		ShaderResourceCBufferData tempData;
		tempData.deltaTime = aDeltaTime.InSeconds();
		tempData.runTime = aRunTime.InSeconds();

		myVariousResources.UpdateData(tempData);
		myVariousResources.BindToPS(1);
	}

	void VisualEffect::SetEffect()
	{
		myVertexLayout = new VisualEffectVertex();

		myVertexLayout->position = Vector4f::Zero;
		myVertexLayout->color = Vector4f(1.f, 0.f, 0.f, 1.f);
		SetTexture(Engine::GetInstance().GetResourceManager().Get<Texture>("Assets/Textures/ShaderTextures/pentagon.dds"));

		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT);
		layout.Add("SIZE", 0, DXGI_FORMAT_R32_FLOAT);
		layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);

		AttachVertexShader("shaders/visualEffects/visualEffectStandard.fx", "VShader", layout);
		AttachGeometryShader("shaders/visualEffects/visualEffectStandard.fx", "GS_Plane");
		AttachPixelShader("shaders/visualEffects/visualEffectStandard.fx", "PS_StandardVisualEffect");
	}

	void VisualEffect::SetTexture(std::shared_ptr<Texture> aShaderTexture)
	{
		myShaderTexture = aShaderTexture;
	}

	void VisualEffect::BindTexture()
	{
		myShaderTexture->BindToPS(0);
	}

	void VisualEffect::DisableEffect()
	{
		if (myVertexLayout != nullptr)
		{
			delete myVertexLayout;
			myVertexLayout = nullptr;
		}
	}

}
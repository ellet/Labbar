#include "stdafx.h"
#include "FullscreenHelper.h"
#include "Engine\Effect\FullscreenEffects\FullscreenEffect.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Texture\MultiRenderTexture.h"
#include "..\Buffer\VertexBuffer.h"

namespace ENGINE_NAMESPACE
{
	FullscreenHelper::FullscreenHelper(unsigned int aWidth, unsigned int aHeight)
	{
		const char * vertexPath = "shaders/fullscreen/vertex.fx";
		const char * vertexEntryPoint = "VShader";

		myEffects.Resize(static_cast<unsigned short>(eFullscreenEffects::eSizeOf));
		myEffects[static_cast<unsigned short>(eFullscreenEffects::eCopy)]					= std::make_shared<FullscreenEffect>(vertexPath, vertexEntryPoint, "shaders/fullscreen/pixelUtility.fx", "PShader_Copy");
		myEffects[static_cast<unsigned short>(eFullscreenEffects::eAdd)]					= std::make_shared<FullscreenEffect>(vertexPath, vertexEntryPoint, "shaders/fullscreen/pixelUtility.fx", "PShader_Add");
		myEffects[static_cast<unsigned short>(eFullscreenEffects::eLuminance)]				= std::make_shared<FullscreenEffect>(vertexPath, vertexEntryPoint, "shaders/fullscreen/pixelBloom.fx", "PShader_Luminance");
		myEffects[static_cast<unsigned short>(eFullscreenEffects::eGaussianBlurHorizontal)] = std::make_shared<FullscreenEffect>(vertexPath, vertexEntryPoint, "shaders/fullscreen/pixelBloom.fx", "PShader_GaussianBlurHorizontal");
		myEffects[static_cast<unsigned short>(eFullscreenEffects::eGaussianBlurVertical)]	= std::make_shared<FullscreenEffect>(vertexPath, vertexEntryPoint, "shaders/fullscreen/pixelBloom.fx", "PShader_GaussianBlurVertical");
		myEffects[static_cast<unsigned short>(eFullscreenEffects::eToneMapping)] = std::make_shared<FullscreenEffect>(vertexPath, vertexEntryPoint, "shaders/fullscreen/pixelHDR.fx", "PShader_Tonemap");
		myEffects[static_cast<unsigned short>(eFullscreenEffects::eMotionBlur)] = std::make_shared<FullscreenEffect>(vertexPath, vertexEntryPoint, "shaders/fullscreen/pixelMotionBlur.fx", "PShader_MotionBlur");



		myVertices[0].position = Vector4f(-1.f, -1.f, 0.5f, 1.f);
		myVertices[1].position = Vector4f(-1.f, 1.f, 0.5f, 1.f);
		myVertices[2].position = Vector4f(1.f, -1.f, 0.5f, 1.f);
		myVertices[3].position = Vector4f(1.f, 1.f, 0.5f, 1.f);
		myVertices[4].position = Vector4f(1.f, -1.f, 0.5f, 1.f);
		myVertices[5].position = Vector4f(-1.f, 1.f, 0.5f, 1.f);

		myVertices[0].uv = Vector2f(0.f, 1.f);
		myVertices[1].uv = Vector2f(0.f, 0.f);
		myVertices[2].uv = Vector2f(1.f, 1.f);
		myVertices[3].uv = Vector2f(1.f, 0.f);
		myVertices[4].uv = Vector2f(1.f, 1.f);
		myVertices[5].uv = Vector2f(0.f, 0.f);

		myVertexBuffer = std::make_unique<VertexBuffer<SpriteVertex>>(myVertices, 6);


		unsigned int smallestSize = min(aWidth, aHeight);

		unsigned int downSample = static_cast<unsigned int> (pow(2, floor(log(smallestSize) / log(2))));

		mySmallestBloomdownsample = std::make_shared<RenderTexture>(256, 256, false);
		while (downSample >= 1)
		{
			myDownsamples.Add(std::make_shared<RenderTexture>(downSample, downSample, false));
			downSample = downSample / 2;
		}

		mySourceTexture = std::make_shared<RenderTexture>(aWidth, aHeight, false);
		myTargetTexture = std::make_shared<RenderTexture>(aWidth, aHeight, false);
		myInputTexture = std::make_shared<RenderTexture>(aWidth, aHeight, false);

	}

	FullscreenHelper::~FullscreenHelper()
	{
	}

	void FullscreenHelper::DoBloom(bool aShowSteps)
	{
		Downsample(256);

		DoEffect(FullscreenHelper::eFullscreenEffects::eLuminance);
		DoEffect(FullscreenHelper::eFullscreenEffects::eGaussianBlurHorizontal);
		DoEffect(FullscreenHelper::eFullscreenEffects::eGaussianBlurVertical);
		DoEffect(FullscreenHelper::eFullscreenEffects::eGaussianBlurHorizontal);
		DoEffect(FullscreenHelper::eFullscreenEffects::eGaussianBlurVertical);
		Interpolate();

		DoEffect(mySourceTexture, myTargetTexture, myInputTexture, eFullscreenEffects::eAdd);
		myInputTexture->GetTexture()->UnbindFromPS(1);
	}

	void FullscreenHelper::DoHDR(bool aShowSteps)
	{
		Downsample(1);
		Interpolate();
		//DoEffect(eFullscreenEffects::eToneMapping);
		DoEffect(mySourceTexture, myTargetTexture, myInputTexture, eFullscreenEffects::eToneMapping);
		myInputTexture->GetTexture()->UnbindFromPS(1);

	}

	void FullscreenHelper::DoMotionBlur()
	{
		DoEffect(mySourceTexture, myTargetTexture, myInputTexture, eFullscreenEffects::eMotionBlur);
	}

	void FullscreenHelper::DrawEffect(FullscreenHelper::eFullscreenEffects aEffect)
	{ 
		myEffects[static_cast<unsigned short> (aEffect)]->Bind();

		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Engine::GetInstance().GetRenderer().GetContext()->Draw(6, 0);
	}

	void FullscreenHelper::CopyInput()
	{
		mySourceTexture->GetTexture()->UnbindFromPS(0);
		mySourceTexture->Bind(0);
		myInputTexture->GetTexture()->BindToPS(0);
		
		myVertexBuffer->Bind(0);
		DrawEffect(eFullscreenEffects::eCopy);
	}

	void FullscreenHelper::DoEffectNoSwap(FullscreenHelper::eFullscreenEffects aEffect, std::shared_ptr<RenderTexture> aTargetTexture, std::shared_ptr<RenderTexture> aResourceTexture)
	{
		aTargetTexture->Bind(0);
		aResourceTexture->GetTexture()->BindToPS(0);

		myVertexBuffer->Bind(0);

		DrawEffect(aEffect);
	}

	void FullscreenHelper::DoEffect(eFullscreenEffects aEffect)
	{
		myTargetTexture->GetTexture()->UnbindFromPS(0);
		myTargetTexture->Bind(0);
		mySourceTexture->GetTexture()->BindToPS(0);
		
		myVertexBuffer->Bind(0);

		DrawEffect(aEffect);

		std::swap(myTargetTexture, mySourceTexture);
	}

	void FullscreenHelper::DoEffect(std::shared_ptr<RenderTexture> aTarget, std::shared_ptr<RenderTexture> aSourceTexture, std::shared_ptr<RenderTexture> aSecondSourceTexture, eFullscreenEffects aFullscreenEffect)
	{
		aSourceTexture->GetTexture()->BindToPS(0);
		aSecondSourceTexture->GetTexture()->BindToPS(1);
		aTarget->Bind(0);
		myVertexBuffer->Bind(0);
		DrawEffect(aFullscreenEffect);

	}

	void FullscreenHelper::DoFullscreenEffects(std::shared_ptr<MultiRenderTexture> & aIntermediateTexture, unsigned int aEffectsToRun, unsigned int aStepsToShow)
	{
		DoEffectNoSwap(FullscreenHelper::eFullscreenEffects::eCopy, myInputTexture, aIntermediateTexture->GetRenderTexture(eRenderTargets::eIntermediate));
		DoEffectNoSwap(FullscreenHelper::eFullscreenEffects::eCopy, mySourceTexture, myInputTexture);

		//myInputTexture = aIntermediateTexture;
		//CopyInput();
		if ((aEffectsToRun & eEffectBundles::eBloom) != 0)
		{
			DoBloom((aStepsToShow & eEffectBundles::eBloom) != 0);
			CopyRenderTexture(myInputTexture, mySourceTexture);
		}
		if ((aEffectsToRun & eEffectBundles::eHDR) != 0)
		{
			DoHDR((aStepsToShow & eEffectBundles::eHDR) != 0);
			CopyRenderTexture(myInputTexture, mySourceTexture);
		}
		
		
		if ((aEffectsToRun & eEffectBundles::eMotionBlur) != 0)
		{
			DoEffect(mySourceTexture, myInputTexture, aIntermediateTexture->GetRenderTexture(eRenderTargets::eVelocity), eFullscreenEffects::eMotionBlur);
			DoEffect(mySourceTexture, myInputTexture, aIntermediateTexture->GetRenderTexture(eRenderTargets::eVelocity), eFullscreenEffects::eAdd);
			CopyRenderTexture(myInputTexture, mySourceTexture);
		}
		

		CopyRenderTexture(aIntermediateTexture->GetRenderTexture(eRenderTargets::eIntermediate), myInputTexture);

	}

	void FullscreenHelper::CopyRenderTexture(std::shared_ptr<RenderTexture> &aTarget, const std::shared_ptr<RenderTexture> &aSource)
	{
		DoEffectNoSwap(eFullscreenEffects::eCopy, aTarget, aSource);
	}

	void FullscreenHelper::Downsample(unsigned int aDestination)
{
		if (myTargetTexture->GetHeight() <= myDownsamples.GetLast()->GetHeight())
		{
			return;
		}

		myFullSizeTextureTarget = myTargetTexture;
		myFullSizeTextureSource = mySourceTexture;

		unsigned short index = 0;
		while (myDownsamples.Size() > index && myDownsamples[index]->GetWidth() >= aDestination)
		{
			myTargetTexture = (myDownsamples[index]);
			index++;
			DoEffect(FullscreenHelper::eFullscreenEffects::eCopy);
		}
		if (aDestination == 256)
		{
			myTargetTexture = mySmallestBloomdownsample;
		}

	}

	void FullscreenHelper::Interpolate()
	{
		DoEffect(FullscreenHelper::eFullscreenEffects::eCopy);
		if (myTargetTexture->GetHeight() < myFullSizeTextureTarget->GetHeight())
		{
			myTargetTexture = myFullSizeTextureTarget;
			DoEffect(FullscreenHelper::eFullscreenEffects::eCopy);
		}
		if (myTargetTexture->GetHeight() < myFullSizeTextureSource->GetHeight())
		{
			myTargetTexture = myFullSizeTextureSource;
			DoEffect(FullscreenHelper::eFullscreenEffects::eCopy);
		}
	}
}

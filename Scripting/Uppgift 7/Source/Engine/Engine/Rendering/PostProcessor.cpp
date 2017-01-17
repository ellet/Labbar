#include "stdafx.h"
#include "PostProcessor.h"
#include "Engine\Effect\FullscreenEffects\FullscreenEffect.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Texture\WorldRenderTexture.h"
#include "..\Buffer\VertexBuffer.h"
#include "Engine/Texture/WorldRenderTexture.h"

namespace SB
{
	PostProcessor::PostProcessor(unsigned int aWidth, unsigned int aHeight)
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

		myMotionBlurData = std::make_shared<ConstantBuffer<MotionBlurConstantData>>();

		myBloomBufferData = std::make_shared<ConstantBuffer<BloomBufferData>>();
		unsigned int smallestSize = max(aWidth, aHeight);

		unsigned int downSample = static_cast<unsigned int> (pow(2, ceil(log(smallestSize) / log(2))));

		mySmallestBloomdownsample = std::make_shared<RenderTexture>(256, 256, false, DXGI_FORMAT_R16G16B16A16_FLOAT);
		while (downSample >= 1)
		{
			myDownsamples.Add(std::make_shared<RenderTexture>(downSample, downSample, false, DXGI_FORMAT_R16G16B16A16_FLOAT));
			downSample = downSample / 2;
		}

		mySourceTexture = std::make_shared<RenderTexture>(aWidth, aHeight, false, DXGI_FORMAT_R16G16B16A16_FLOAT);
		myTargetTexture = std::make_shared<RenderTexture>(aWidth, aHeight, false, DXGI_FORMAT_R16G16B16A16_FLOAT);
		myInputTexture = std::make_shared<RenderTexture>(aWidth, aHeight, false, DXGI_FORMAT_R16G16B16A16_FLOAT);

	}

	PostProcessor::~PostProcessor()
	{
	}

	void PostProcessor::DoBloom(bool aShowSteps)
	{
		myBloomBufferData->UpdateData(BloomBufferData(myBloomAmount, myAllowBloomModification, myXCameraSpacePos, myYCameraSpacePos));
		myBloomBufferData->BindToPS(4);
		RenderingEventGroup event(L"Bloom");
		Downsample(256);

		DoEffect(PostProcessor::eFullscreenEffects::eLuminance);
		DoEffect(PostProcessor::eFullscreenEffects::eGaussianBlurHorizontal);
		DoEffect(PostProcessor::eFullscreenEffects::eGaussianBlurVertical);
		DoEffect(PostProcessor::eFullscreenEffects::eGaussianBlurHorizontal);
		DoEffect(PostProcessor::eFullscreenEffects::eGaussianBlurVertical);
		Interpolate();

		DoEffect(mySourceTexture, myTargetTexture->GetTexture(0), myInputTexture->GetTexture(0), eFullscreenEffects::eAdd);
		myInputTexture->GetTexture(0)->UnbindFromPS(1);
	}

	void PostProcessor::DoHDR(bool aShowSteps)
	{
		RenderingEventGroup event(L"HDR");
		Downsample(1);
		Interpolate();
		DoEffect(mySourceTexture, myTargetTexture->GetTexture(0), myInputTexture->GetTexture(0), eFullscreenEffects::eToneMapping);
		//DoEffect(eFullscreenEffects::eToneMapping);
		myInputTexture->GetTexture(0)->UnbindFromPS(1);

	}

	void PostProcessor::DoMotionBlur()
	{
		DoEffect(mySourceTexture, myTargetTexture->GetTexture(0), myInputTexture->GetTexture(0), eFullscreenEffects::eMotionBlur);
	}

	void PostProcessor::DrawEffect(PostProcessor::eFullscreenEffects aEffect)
	{ 
		myEffects[static_cast<unsigned short> (aEffect)]->Bind();

		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Engine::GetInstance().GetRenderer().GetContext()->Draw(6, 0);
	}

	void PostProcessor::CopyInput()
	{
		mySourceTexture->GetTexture(0)->UnbindFromPS(0);
		mySourceTexture->Bind(0);
		myInputTexture->GetTexture(0)->BindToPS(0);
		
		myVertexBuffer->Bind(0);
		DrawEffect(eFullscreenEffects::eCopy);
	}

	void PostProcessor::DoEffectNoSwap(eFullscreenEffects aEffect, const std::shared_ptr<RenderTexture> & aTargetTexture, const std::shared_ptr<Texture> & aResourceTexture)
	{
		aTargetTexture->Bind(0);
		aResourceTexture->BindToPS(0);

		myVertexBuffer->Bind(0);

		DrawEffect(aEffect);
	}

	void PostProcessor::DoEffect(eFullscreenEffects aEffect)
	{
		myTargetTexture->GetTexture(0)->UnbindFromPS(0);
		myTargetTexture->Bind(0);
		mySourceTexture->GetTexture(0)->BindToPS(0);
		
		myVertexBuffer->Bind(0);

		DrawEffect(aEffect);

		std::swap(myTargetTexture, mySourceTexture);
	}
	void PostProcessor::DoEffect(const std::shared_ptr<RenderTexture> & aTarget, const std::shared_ptr<Texture> & aSourceTexture, const std::shared_ptr<Texture> & aSecondSourceTexture, eFullscreenEffects aFullscreenEffect, bool aBindSourcesFirst /*= true*/)
	{
		if (aBindSourcesFirst == true)
		{
			aSourceTexture->BindToPS(0);
			aSecondSourceTexture->BindToPS(1);
			aTarget->Bind(0);
		}
		else
		{
			aTarget->Bind(0);
			aSourceTexture->BindToPS(0);
			aSecondSourceTexture->BindToPS(1);
		}
		myVertexBuffer->Bind(0);
		DrawEffect(aFullscreenEffect);

	}

	void PostProcessor::DoFullscreenEffects(const std::shared_ptr<WorldRenderTexture> & aWorldTexture, unsigned int aEffectsToRun, unsigned int aStepsToShow)
	{
		RenderingEventGroup event(L"Post-processing");

		{
			RenderingEventGroup clears(L"Clears");
			mySmallestBloomdownsample->Clear(SB::Vector4f::Zero);
			for (unsigned short i = 0; i < myDownsamples.Size(); i++)
			{
				myDownsamples[i]->Clear(SB::Vector4f::Zero);
			}

			mySourceTexture->Clear(SB::Vector4f::Zero);
			myTargetTexture->Clear(SB::Vector4f::Zero);
			myInputTexture->Clear(SB::Vector4f::Zero);
		}

		DoEffectNoSwap(PostProcessor::eFullscreenEffects::eCopy, myInputTexture, aWorldTexture->GetTexture(WorldRenderTarget::eDiffuse));
		DoEffectNoSwap(PostProcessor::eFullscreenEffects::eCopy, mySourceTexture, myInputTexture->GetTexture(0));

		//myInputTexture = aIntermediateTexture;
		//CopyInput();
		if ((aEffectsToRun & eEffectBundles::eBloom) != 0)
		{
			DoBloom((aStepsToShow & eEffectBundles::eBloom) != 0);
			CopyRenderTexture(myInputTexture, mySourceTexture->GetTexture(0));
		}
		else
		{
			RenderingEvent(L"Bloom is disabled");
		}

		if ((aEffectsToRun & eEffectBundles::eHDR) != 0)
		{
			DoHDR((aStepsToShow & eEffectBundles::eHDR) != 0);
			CopyRenderTexture(myInputTexture, mySourceTexture->GetTexture(0));
		}
		else
		{
			RenderingEvent(L"HDR is disabled");
		}


		if ((aEffectsToRun & eEffectBundles::eMotionBlur) != 0)
		{
			RenderingEventGroup motionBlurEvent(L"Motion Blur");

			MotionBlurConstantData data;
			data.blurMultiplier = Engine::GetDeltaTime().InMilliseconds() * 0.03f;
			myMotionBlurData->UpdateData(data);
			myMotionBlurData->BindToPS(4);

			DoEffect(myTargetTexture, aWorldTexture->GetTexture(WorldRenderTarget::eVelocity), myInputTexture->GetTexture(0), eFullscreenEffects::eMotionBlur, false);
			//DoEffect(mySourceTexture, myTargetTexture, myInputTexture, eFullscreenEffects::eAdd, false);
			myInputTexture->GetTexture(0)->UnbindFromPS(1);
			CopyRenderTexture(myInputTexture, myTargetTexture->GetTexture(0));
		}
		else
		{
			RenderingEvent(L"Motion Blur is disabled");
		}

		CopyRenderTexture(aWorldTexture, myInputTexture->GetTexture(0));
	}

	void PostProcessor::CopyRenderTexture(const std::shared_ptr<RenderTexture> &aTarget, const std::shared_ptr<Texture> &aSource)
	{
		DoEffectNoSwap(eFullscreenEffects::eCopy, aTarget, aSource);
	}


	void PostProcessor::AllowBloomModification(bool aValue)
	{
		if (aValue == true)
		{
			myAllowBloomModification = 1.0f;
		}
		else
		{
			myAllowBloomModification = 0.0f;
		}
	}

	void PostProcessor::Downsample(unsigned int aDestination)
{
		RenderingEventGroup event((std::wstring(L"Downsample to ") + std::to_wstring(aDestination)).c_str());

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
			DoEffect(PostProcessor::eFullscreenEffects::eCopy);
		}
		if (aDestination == 256)
		{
			myTargetTexture = mySmallestBloomdownsample;
		}

	}

	void PostProcessor::Interpolate()
	{
		RenderingEventGroup event(L"Scale to rendering resolution");


		DoEffect(PostProcessor::eFullscreenEffects::eCopy);
		if (myTargetTexture->GetHeight() < myFullSizeTextureTarget->GetHeight())
		{
			myTargetTexture = myFullSizeTextureTarget;
			DoEffect(PostProcessor::eFullscreenEffects::eCopy);
		}
		if (myTargetTexture->GetHeight() < myFullSizeTextureSource->GetHeight())
		{
			myTargetTexture = myFullSizeTextureSource;
			DoEffect(PostProcessor::eFullscreenEffects::eCopy);
		}

	}
}

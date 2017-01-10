#include "stdafx.h"
#include "Engine\Rendering\SpriteRenderer.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Sprite\Sprite.h"
#include "Engine\Sprite\QuadSpriteShape.h"
#include "Engine\Sprite\FullscreenQuadSpriteShape.h"
#include "Engine\Sprite\SpriteEffect.h"

namespace SB
{

	SpriteRenderer::SpriteRenderer()
	{
		myInstanceBuffers.Add(new VertexBuffer<SpriteInstanceData>(nullptr, 4, false));

		mySpriteEffect = std::make_shared<SpriteEffect>();
		//myInstanceBuffer = std::make_unique<VertexBuffer<SpriteInstanceData>>(nullptr, 1, false);
		myQuad = std::make_unique<QuadSpriteShape>();
		myFullscreenQuad = std::make_unique<FullscreenQuadSpriteShape>();
	}

	SpriteRenderer::~SpriteRenderer()
	{
		myInstanceBuffers.DeleteAll();
	}

	void SpriteRenderer::Render(const Sprite &aSprite)
	{
		if (myCurrentSpriteEffect != aSprite.GetEffect() || myCurrentSpriteTexture != aSprite.GetTexture())
		{
			RenderBuffer();

			myCurrentSpriteEffect = aSprite.GetEffect();
			myCurrentSpriteTexture = aSprite.GetTexture();
		}

		SpriteInstanceData data;
		data.toWorld = aSprite.GenerateMatrix();
		data.color = aSprite.GetColor();
		data.textureTopLeft = aSprite.GetTextureRectTopLeft() / aSprite.GetTexture()->GetSize();
		data.textureSize = aSprite.GetTextureRectSize() / aSprite.GetTexture()->GetSize();

		myInstanceData.Add(data);
	}


	void SpriteRenderer::RenderBuffer()
	{
		if (myInstanceData.Size() == 0)
		{
			return;
		}

		const std::shared_ptr<const Effect> & effect = myCurrentSpriteEffect;
		if (effect != nullptr)
		{
			if (std::const_pointer_cast<Effect>(effect)->Prepare(true) == false)
			{
				return;
			}
			effect->Bind();
		}
		else
		{
			if (std::const_pointer_cast<SpriteEffect>(mySpriteEffect)->Prepare(true) == false)
			{
				return;
			}
			mySpriteEffect->Bind();
		}

		SetupInstanceBufferAndBind();

		

		myCurrentSpriteTexture->BindToPS(0);
		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Engine::GetRenderer().DisableDepthWriteRead();
		myQuad->RenderInstanced(myInstanceData.Size());
		myInstanceData.RemoveAll();
		Engine::GetRenderer().EnableDepth();
	}

	void SpriteRenderer::RenderFullscreenQuad(const std::shared_ptr<Texture>& aTexture, std::shared_ptr<const Effect> aEffect)
	{
		if (aEffect != nullptr)
		{
			if (std::const_pointer_cast<Effect>(aEffect)->Prepare(true) == false)
			{
				return;
			}
			aEffect->Bind();
		}
		else
		{
			if (std::const_pointer_cast<SpriteEffect>(mySpriteEffect)->Prepare(true) == false)
			{
				return;
			}
			mySpriteEffect->Bind();
		}


		SpriteInstanceData data;
		data.toWorld = Matrix44f::Identity;
		data.color = Vector4f::One;
		data.textureTopLeft = Vector2f::Zero;
		data.textureSize = Vector2f::One;
		myInstanceBuffers[0]->UpdateData(&data, 1);
		myInstanceBuffers[0]->Bind(1);

		if (aTexture != nullptr)
		{
			aTexture->BindToPS(0);
		}
		else
		{
			ID3D11ShaderResourceView * views[1] = { nullptr };
			Engine::GetInstance().GetRenderer().GetContext()->PSSetShaderResources(0, 1, views);
		}
		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Engine::GetRenderer().DisableDepthWriteRead();
		myFullscreenQuad->RenderInstanced(1);
		Engine::GetRenderer().EnableDepth();
	}


	void SpriteRenderer::SetupInstanceBufferAndBind()
	{
		VertexBuffer<SpriteInstanceData> * currentBuffer = &*myInstanceBuffers[0];

		unsigned short bufferCounter = 0;
		while (currentBuffer->GetCount() < myInstanceData.Size())
		{
			++bufferCounter;
			if (bufferCounter >= myInstanceBuffers.Size())
			{
				myInstanceBuffers.Add(new VertexBuffer<SpriteInstanceData>(nullptr ,currentBuffer->GetCount() * 2, false));
			}

			currentBuffer = &*myInstanceBuffers[bufferCounter];
		}

		currentBuffer->UpdateData(&myInstanceData[0], myInstanceData.Size());
		currentBuffer->Bind(1);
	}


}

#include "stdafx.h"
#include "Engine\Texture\TextureDebugger.h"
#include "Engine\Rendering\DXRenderer.h"
#include "Engine\Texture\Texture.h"
#include "Engine\Effect\Effect.h"
#include "Engine\Effect\InputLayout.h"
#include "Engine\Model\Model.h"
#include "Engine\Buffer\DepthBuffer.h"
#include "Engine\Texture\RenderTexture.h"
#include "Engine\Model\Mesh.h"
#include "Engine/Sprite/SpriteVertex.h"
#include "Engine/Rendering/SpriteRenderer.h"

namespace SB
{
	TextureDebugger::TextureDebugger(const unsigned int aNewWidth, const unsigned int aNewHeight)
	{
		Resize(aNewWidth, aNewHeight);
	}


	TextureDebugger::~TextureDebugger()
	{
	}

	void TextureDebugger::Resize(const unsigned int aNewWidth, const unsigned int aNewHeight)
	{
		myRenderTexture = std::make_unique<RenderTexture>(aNewWidth, aNewHeight, false, nullptr);
	}

	void TextureDebugger::Render()
	{
		// Engine::GetRenderer().GetSpriteRenderer().RenderFullscreenQuad(myRenderTexture->GetTexture(0));
		// myRenderTexture->Clear(SB::Vector4f::Zero);
		// const float width = static_cast<float>(Engine::GetEngineSettings().GetResolution().y) * 0.25f;
		// mySprite.SetPosition(SB::Vector2f(myRenderTexture->GetTexture()->GetSize().x - width, 0.f));
	}

	void TextureDebugger::QueueRender(std::shared_ptr<Texture> aTextureToView)
	{
		// const float height = static_cast<float>(Engine::GetEngineSettings().GetResolution().y) * 0.25f;
		// 
		// myRenderTexture->Bind(0);
		// 
		// mySprite.SetTexture(aTextureToView);
		// mySprite.SetScale(SB::Vector2f(height, height) / SB::Vector2f(mySprite.GetTextureRectSize()));
		// mySprite.Render();
		// 
		// mySprite.SetPosition(mySprite.GetPosition() + Vector2f(0.f, height));
	}
}

#include "stdafx.h"
#include "videoplayer/video.h"
#include "videoplayer/videoplayer.h"
#include "sprite/sprite.h"
#include "d3d/direct_3d.h"
#include "sprite/textured_quad.h"
#include "texture/texture_manager.h"

using namespace Tga2D;
Tga2D::CVideo::CVideo()
	:myPlayer(nullptr)
{
	myBuffer = nullptr;
	myUpdateTime = 0.0f;
	myStatus = VideoStatus_Idle;
	myWantsToPlay = false;
	myTexture = nullptr;
	myShaderResource = nullptr;
	mySprite = nullptr;
	myIsLooping = false;
}

Tga2D::CVideo::~CVideo()
{
	SAFE_RELEASE(myTexture);
	SAFE_RELEASE(myShaderResource);

	if (mySprite)
	{
		delete mySprite;
		mySprite = nullptr;
	}

	if (myBuffer)
	{
		delete[] myBuffer;
	}

	delete myPlayer;
	myPlayer = nullptr;
	
}

void Tga2D::CVideo::Play(bool aLoop)
{
	myWantsToPlay = true;
	myIsLooping = aLoop;
}

void Tga2D::CVideo::Pause()
{
	myWantsToPlay = false;
}

void Tga2D::CVideo::Stop()
{
	myWantsToPlay = false;
	myPlayer->Stop();
}

void Tga2D::CVideo::Restart()
{
	myWantsToPlay = true;
	myPlayer->RestartStream();
}

bool CVideo::Init(const char* aPath)
{
	if (myPlayer)
	{
		return false;
	}

	myPlayer = new CVideoPlayer();
	if (myPlayer)
	{
		if (!myPlayer->Init(aPath))
		{
			ERROR_PRINT("%s %s %s", "Could not load video: ", aPath, ". Wrong format?");
			return false;
		}
	}

	myShaderResource = nullptr;

	mySprite = new CSprite(nullptr);

	if (!myPlayer->DoFirstFrame())
	{
		ERROR_PRINT("%s %s %s", "Video error: ", aPath, ". First frame not found?");
		return false;
	}
	
	mySize.x = myPlayer->l_pAVFrame->width;
	mySize.y = myPlayer->l_pAVFrame->height;

	myBuffer = new int[(mySize.x*mySize.y)];

	myStatus = VideoStatus_Playing;

	

	if (!myShaderResource)
	{
		D3D11_TEXTURE2D_DESC texture_desc;
		texture_desc.Width = mySize.x;
		texture_desc.Height = mySize.y;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;
		texture_desc.MipLevels = 1;
		texture_desc.ArraySize = 1;

		texture_desc.SampleDesc.Count = 1;
		texture_desc.SampleDesc.Quality = 0;
		texture_desc.Usage = D3D11_USAGE_DYNAMIC;
		texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		texture_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		texture_desc.MiscFlags = 0;

		CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateTexture2D(&texture_desc, nullptr, &myTexture);
		CEngine::GetInstance()->GetDirect3D().GetDevice()->CreateShaderResourceView(myTexture, NULL, &myShaderResource);

		mySprite->GetTexturedQuad()->myTexture->myResource = myShaderResource;

		Tga2D::Vector2f texSize = CEngine::GetInstance()->GetTextureManager().GetTextureSize(myShaderResource);


		mySprite->SetSize(Tga2D::Vector2f(texSize.x, texSize.y));
		mySprite->SetTextureRect(0, 0, 1, 1);
	}



	return true;
}

void CVideo::Update(float aDelta)
{
	if (!myWantsToPlay || !myPlayer)
	{
		return;
	}
	myUpdateTime += aDelta;

	double fps = myPlayer->GetFps();

	if (myUpdateTime >= 1.0f / fps)
	{
		if (myShaderResource && myTexture)
		{
			int status = myPlayer->GrabNextFrame();
			if (status < 0)
			{
				myStatus = VideoStatus_ReachedEnd;
				if (myIsLooping)
				{
					Restart();
				}
			}

			CDirectEngine& engine = CEngine::GetInstance()->GetDirect3D();
			D3D11_MAPPED_SUBRESOURCE  mappedResource;
			HRESULT result = engine.GetContext()->Map(myTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			if (FAILED(result))
			{
				return;
			}

			int* source = (int*)(mappedResource.pData);


			myPlayer->Update(source);

			engine.GetContext()->Unmap(myTexture, 0);
			

		}
		myUpdateTime = 0.0f;
	}
}

bool CVideo::Render()
{
	if (mySprite && myShaderResource)
	{
		mySprite->GetTexturedQuad()->myTexture->myResource = myShaderResource;
		// Video is upside down - Rescale size and add 1 to pos Y
		Tga2D::Vector2f size = mySprite->GetSize();
		Tga2D::Vector2f pos = mySprite->GetPosition();

/*
		mySprite->SetSize(Tga2D::Vector2f(size.x, -size.y));
		mySprite->SetPosition(Tga2D::Vector2f(pos.x, pos.y + 1.0f));*/
		mySprite->Render();

		// Reset to previous values
/*
		mySprite->SetSize(size);
		mySprite->SetPosition(pos);*/
		return true;
	}
	return false;
}

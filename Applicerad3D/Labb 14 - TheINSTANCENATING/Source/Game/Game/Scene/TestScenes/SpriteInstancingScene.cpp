#include "stdafx.h"
#include "SpriteInstancingScene.h"
#include "Engine\Sprite\Sprite.h"


const size_t SpriteAmount = 100000;

SpriteInstancingScene::SpriteInstancingScene(SB::PostMasterState & aPostMasterState)
	: SB::Scene(aPostMasterState, "SpriteTestingScene")
{
	mySprites.Resize(SpriteAmount);
	for (size_t iSprite = 0; iSprite < SpriteAmount; ++iSprite)
	{
		 mySprites[iSprite].SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Assets/Textures/SmallSmallOrangeLogo.dds"));

		 float x = myRandomizer.GetRandomValue(0.f, 1280.f - mySprites[iSprite].GetTexture()->GetSize().x);
		 float y = myRandomizer.GetRandomValue(0.f, 720.f - mySprites[iSprite].GetTexture()->GetSize().y);
		 mySprites[iSprite].SetPosition(SB::Vector2f(x, y));
		 mySprites[iSprite].SetScale(SB::Vector2f::One * 0.1f);
	}
}


SpriteInstancingScene::~SpriteInstancingScene()
{
}

void SpriteInstancingScene::Update(const SB::Time & aDeltaTime)
{
	Scene::Update(aDeltaTime);
}

void SpriteInstancingScene::Render()
{
	Scene::Render();
	for (size_t iSprite = 0; iSprite < mySprites.Size(); ++iSprite)
	{
		mySprites[iSprite].Render();
	}

}

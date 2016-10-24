#pragma once
#include <Engine\Scene\Scene.h>

#include <Engine/Text/Text.h>


class TextScene :
	public SB::Scene
{
public:
	TextScene();
	~TextScene();

	virtual void Update(const SB::Time & aDeltaTime) override;


	virtual void Render() override;
private:
	SB::Text myText;
	SB::Text myText2;

};


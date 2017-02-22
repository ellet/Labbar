#pragma once
#include "GameCode\Components\BaseComponent.h"
#include <tga2d\math\vector2.h>

namespace DX2D
{
	class CSprite;
}

class RenderComponent : public CBaseComponent
{
public:
	RenderComponent();
	~RenderComponent();

	void LoadSprite(const std::string & aFilePath);



	virtual void Render() override;


	const DX2D::Vector2f & GetSize() const;

	static unsigned int myID;
private:
	DX2D::CSprite * mySprite;
};


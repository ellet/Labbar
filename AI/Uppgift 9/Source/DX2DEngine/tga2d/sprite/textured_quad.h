#pragma once
#include "render/render_object.h"
#include "render/render_common.h"

namespace Tga2D
{
	struct STextureRext
	{
		float myStartX;
		float myStartY;
		float myEndX;
		float myEndY;
	};
	struct ID3D11Resource;
	class CEngine;
	class CTextureManager;
	class CTexture;
	class CTexturedQuad : public CRenderObjectSprite
	{
	public:
		CTexturedQuad(void);
		~CTexturedQuad(void);
		void Init(const char* aTexturePath);
		void Render();
		void SetTextureRect(float aStartX, float aStartY, float aEndX, float aEndY);
		CEngine* myEngine;	
		CTexture* myTexture;

		STextureRext& GetTextureRect(){return myTextureRect;}
		void SetColor(const CColor aColor);
		const CColor& GetColor() const;
		const CColor& GetColor();
		void SetSize(const Vector2f& aSize);
		virtual void SetUV(const Vector2f& aUV);
		void SetMap(EShaderMap aMapType, const char* aPath);
		
		CTexture* myMaps[MAP_MAX];
		class CCustomShader* myCustomShader;
	private:
		STextureRext myTextureRect;
	};
}

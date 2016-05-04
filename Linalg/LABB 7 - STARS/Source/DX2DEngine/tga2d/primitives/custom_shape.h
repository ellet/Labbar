#pragma once
#include "tga2d/render/render_object.h"

namespace DX2D
{
	class CCustomShape : public CRenderObjectCustom
	{
	public:
		CCustomShape();
		~CCustomShape();

		// Do this first, must be %3 (3, 6, 9, 12 etc..)
		void Reset();
		int AddPoint(DX2D::Vector2f aPoint, CColor aColor);
		void SetColorOnPoint(int aIndex, CColor aColor);
		void RemovePoints(int aIndex);

		// Do this second
		void BuildShape();
		void Render();
	private:
		int myIndex;
		bool myIsDirty;
	};
}
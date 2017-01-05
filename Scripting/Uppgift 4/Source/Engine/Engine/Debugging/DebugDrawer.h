#pragma once
#include "LineVertex.h"

namespace SB
{

	class DebugDrawer
	{
	public:
		DebugDrawer();

		void DrawLine(const Camera & aCamera, const Vector3f & aFrom, const Vector3f & aTo, const Color & aColor);
		void DrawLine(const Camera & aCamera, const LineSegmentShape & aLineToDraw, const Color & aColor = Color::White);
		void RenderShape(const Camera & aCamera, const SphereShape & aSphereShape, const Color & aColor = Color::White);
		void RenderShape(const Camera & aCamera, const LineSegmentShape & aLine, const Color & aColor = Color::White);
		void RenderShape(const Camera & aCamera, const CapsuleShape & aCapsule, const Color & aColor = Color::White);
		void RenderSphere(const Camera & aCamera, const Vector3f & aPosition, const float aRadius, const Color & aColor = Color::White);
		void RenderSphere(const Camera & aCamera, const Vector3f & aPosition, const Vector3f &aRadiusconst, const Color & aColor = Color::White);

		void RenderCube(const Camera & aCamera, const Vector3f & aCenterPosition, const Vector3f &aSize, const Color & aColor = Color::White);
		void RenderCube(const Camera & aCamera, const Vector3f & aCenterPosition, const Vector3f &aSize, const Quaternion & aRotation, const Color & aColor = Color::White);

		void DrawCone(const Camera & aCamera, const Vector3f& aFrom, const Vector3f& aDirection, const Color& aColor);
		void RenderArrow(const Camera & aCamera, const Vector3f & aFrom, const Vector3f & aTo, const Color & aColor);
		void RenderArrow(const Camera & aCamera, const LineSegmentShape & aLineSegment, const Color & aColor);

		void DrawCircle(const GuiRenderTarget & aGUIRenderTarget,const SB::Vector2f aPosition, const float aRadius, const SB::Vector4f aColor = SB::Vector4f(1.f, 1.f, 1.f, 0.2f));

	private:
		void DrawShape(const Camera & aCamera, const std::shared_ptr<Model> & aShape, const Vector3f & aPosition, const Vector3f & aScale, const Color & aColor = Color::White, const Quaternion & aRotation = Quaternion(), bool aDrawWireframe = true);

		std::shared_ptr<Effect> myLineEffect;
		std::shared_ptr<VertexBuffer<LineVertex>> myLineVertexBuffer;

		Sprite myCircleSprite;

		std::shared_ptr<Model> mySphereModel;
		std::shared_ptr<Effect> myWireframeEffect;
		std::shared_ptr<Model> myCubeModel;
		std::shared_ptr<Model> myConeModel;
	};
}
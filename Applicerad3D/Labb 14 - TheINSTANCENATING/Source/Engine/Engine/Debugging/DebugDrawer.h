#pragma once
#include "LineVertex.h"

namespace ENGINE_NAMESPACE
{

	class DebugDrawer
	{
	public:
		DebugDrawer();

		void DrawLine(const Vector3f & aFrom, const Vector3f & aTo, const Vector4f & aColor);
		void DrawLine(const LineSegmentShape & aLineToDraw, const Vector4f & aColor = Vector4f::One);
		void RenderShape(const SphereShape & aSphereShape, const Vector4f & aColor = Vector4f::One);
		void RenderShape(const LineSegmentShape & aLine, const Vector4f & aColor = Vector4f::One);
		void RenderShape(const CapsuleShape & aCapsule, const Vector4f & aColor = Vector4f::One);
		void RenderSphere(const Vector3f & aPosition, const float aRadius, const Vector4f & aColor = Vector4f::One);
		void RenderSphere(const Vector3f & aPosition, const Vector3f &aRadiusconst, const Vector4f & aColor = Vector4f::One);

		void RenderCube(const Vector3f & aCenterPosition, const Vector3f &aSize, const Vector4f & aColor = Vector4f::One);

	private:
		void DrawShape(const std::shared_ptr<Model> & aShape, const Vector3f & aPosition, const Vector3f & aScale, const Vector4f & aColor = Vector4f::One);

		std::shared_ptr<Effect> myLineEffect;
		std::shared_ptr<VertexBuffer<LineVertex>> myLineVertexBuffer;

		std::shared_ptr<Model> mySphereModel;
		std::shared_ptr<Effect> myWireframeEffect;
		std::shared_ptr<Model> myCubeModel;
	};
}
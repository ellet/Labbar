#pragma once
#include "LineVertex.h"

namespace ENGINE_NAMESPACE
{
	class Debugger
	{
	public:
		Debugger(void * aWindowHandle);
		~Debugger();

		void NewFrame();
		void RenderFrame();

		void DrawLine(const Vector3f & aFrom, const Vector3f & aTo, const Vector4f & aColor);
		void RenderSphere(const Vector3f & aPosition, const float aRadius);
		void RenderSphere(const Vector3f & aPosition, const Vector3f &aRadius);

		void RenderCube(const Vector3f & aCenterPosition, const Vector3f &aSize);
	private:
		void DrawShape(const std::shared_ptr<Model> & aShape, const Vector3f & aPosition, const Vector3f & aScale);

		std::shared_ptr<Effect> myLineEffect;
		std::shared_ptr<VertexBuffer<LineVertex>> myLineVertexBuffer;

		std::shared_ptr<Model> mySphereModel;
		std::shared_ptr<Effect> myWireframeEffect;
		std::shared_ptr<Model> myCubeModel;
	};
}

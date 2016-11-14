#include "stdafx.h"
#include "DebugDrawer.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Model\AssimpModel.h"
#include "..\Effect\StandardEffect.h"
#include "..\Model\CubeModel.h"




namespace ENGINE_NAMESPACE
{

	DebugDrawer::DebugDrawer()
	{
		myLineEffect = std::make_shared<Effect>();
		myLineEffect->AttachVertexShader("shaders/debugging/line.fx", "VShader");
		myLineEffect->AttachPixelShader("shaders/debugging/line.fx", "PShader");
		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		myLineEffect->Link(layout);

		myLineVertexBuffer = std::make_shared<VertexBuffer<LineVertex>>(nullptr, 2, false);

		myWireframeEffect = std::make_shared<StandardEffect>("shaders/pbr/vertex.fx", "VShader", "shaders/pbr/wireframe.fx", "PShader");

		mySphereModel = Engine::GetResourceManager().Get<AssimpModel>("Assets/Models/Lightspheres/lightsphere_1.fbx");
		myCubeModel = std::make_shared<CubeModel>(nullptr);
	}

	void DebugDrawer::DrawLine(const Vector3f & aFrom, const Vector3f & aTo, const Vector4f & aColor)
	{
		std::array<LineVertex, 2> vertices;
		vertices[0].position = Vector4f(aFrom, 1.f);
		vertices[0].color = aColor;
		vertices[1].position = Vector4f(aTo, 1.f);
		vertices[1].color = aColor;

		myLineVertexBuffer->UpdateData(&vertices[0], 2, false);
		myLineVertexBuffer->Bind(0);

		myLineEffect->Bind();
		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		Engine::GetInstance().GetRenderer().GetContext()->Draw(2, 0);
	}

	void DebugDrawer::DrawLine(const LineSegmentShape & aLineToDraw, const Vector4f & aColor /*= Vector4f::One*/)
	{
		DrawLine(aLineToDraw.myFirstPosition, aLineToDraw.mySecondPosition, aColor);
	}

	void DebugDrawer::RenderShape(const SphereShape & aSphereShape, const Vector4f & aColor)
	{
		RenderSphere(aSphereShape.myPosition, aSphereShape.myRadius, aColor);
	}

	void DebugDrawer::RenderShape(const LineSegmentShape & aLine, const Vector4f & aColor /*= Vector4f::One*/)
	{
		DrawLine(aLine, aColor);
	}

	void DebugDrawer::RenderShape(const CapsuleShape & aCapsule, const Vector4f & aColor /*= Vector4f::One*/)
	{
		Vector3f tempSecondPosition = aCapsule.myFirstPosition + aCapsule.myLengthAndDirection;
		Vector3f tempMidPoint = aCapsule.myFirstPosition + (aCapsule.myLengthAndDirection / 2);

		RenderSphere(aCapsule.myFirstPosition, aCapsule.myRadius, aColor);
		RenderSphere(tempSecondPosition, aCapsule.myRadius, aColor);
		RenderSphere(tempMidPoint, aCapsule.myRadius, aColor);

		Vector3f firstLineOfPlane =  aCapsule.myLengthAndDirection;

		Vector3f extraValue = firstLineOfPlane;

		Quaternion tempRotation;
		tempRotation.RotateAroundLocalX(1.f);
		tempRotation.RotateAroundLocalY(.7f);
		tempRotation.RotateAroundLocalZ(.3f);
		extraValue = tempRotation * extraValue;

		Vector3f tempExtraPoint = Vector3f(firstLineOfPlane + extraValue);
		Vector3f secondLineOfPlane = (tempSecondPosition + tempExtraPoint) - aCapsule.myFirstPosition;

		Vector3f normalOfPlane = firstLineOfPlane.Cross(secondLineOfPlane);
		normalOfPlane = normalOfPlane.Normalize(normalOfPlane);

		Vector3f distanceOffset = normalOfPlane * aCapsule.myRadius;		

		Vector3f capsuleLineEdgeFirstPoint = aCapsule.myFirstPosition + distanceOffset;
		Vector3f capsuleLineEdgeSecondPoint = tempSecondPosition + distanceOffset;

		DrawLine(capsuleLineEdgeFirstPoint, capsuleLineEdgeSecondPoint, aColor);
		DrawLine(aCapsule.myFirstPosition - distanceOffset, tempSecondPosition - distanceOffset, aColor);
	}

	void DebugDrawer::RenderSphere(const Vector3f & aPosition, const float aRadius, const Vector4f & aColor)
	{
		RenderSphere(aPosition, Vector3f::One * aRadius, aColor);
	}

	void DebugDrawer::RenderSphere(const Vector3f & aPosition, const Vector3f &aRadius, const Vector4f & aColor)
	{
		DrawShape(mySphereModel, aPosition, aRadius, aColor);
	}

	void DebugDrawer::RenderCube(const Vector3f & aCenterPosition, const Vector3f &aSize, const Vector4f & aColor)
	{
		DrawShape(myCubeModel, aCenterPosition, aSize, aColor);
	}

	

	void DebugDrawer::DrawShape(const std::shared_ptr<Model> & aShape, const Vector3f & aPosition, const Vector3f & aScale, const Vector4f & aColor)
	{
		Engine::GetRenderer().EnableWireframe();
		Matrix44f m = SB::Matrix44f::CreateScale(aScale.x * 1.0f, aScale.y * 1.0f, aScale.z * 1.0f) * SB::Matrix44f::CreateTranslation(aPosition);
		aShape->InstantRender(myWireframeEffect, m, m, aColor);
		Engine::GetRenderer().DisableWireframe();
	}
}
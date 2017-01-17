#include "stdafx.h"
#include "DebugDrawer.h"
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Model\AssimpModel.h"
#include "..\Effect\StandardEffect.h"
#include "..\Model\CubeModel.h"
#include "..\Camera\Camera.h"
#include "..\Texture\WorldRenderTexture.h"
#include "..\Texture\GuiRenderTarget.h"




namespace SB
{

	DebugDrawer::DebugDrawer()
	{
#ifndef PUBLISH
		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);

		myCircleSprite.SetTexture(SB::Engine::GetResourceManager().Get<SB::Texture>("Sprites/range.dds"));

		myLineEffect = std::make_shared<Effect>();
		myLineEffect->AttachVertexShader("shaders/debugging/line.fx", "VShader", layout);
		myLineEffect->AttachPixelShader("shaders/debugging/line.fx", "PShader");

		myLineVertexBuffer = std::make_shared<VertexBuffer<LineVertex>>(nullptr, 2, false);

		myWireframeEffect = std::make_shared<StandardEffect>("shaders/pbr/vertex.fx", "VShader", "shaders/pbr/wireframe.fx", "PShader");

		mySphereModel = Engine::GetResourceManager().Get<AssimpModel>("Assets/Models/Lightspheres/lightsphere_1.fbx");
		myCubeModel = std::make_shared<CubeModel>(nullptr);
		myConeModel = Engine::GetResourceManager().Get<AssimpModel>("Assets/Models/Cones/cone.fbx");
#endif
	}

	void DebugDrawer::DrawLine(const Camera & aCamera, const Vector3f & aFrom, const Vector3f & aTo, const Color & aColor)
	{
#ifndef PUBLISH
		std::array<LineVertex, 2> vertices;
		vertices[0].position = Vector4f(aFrom, 1.f);
		vertices[0].color = aColor;
		vertices[1].position = Vector4f(aTo, 1.f);
		vertices[1].color = aColor;

		myLineVertexBuffer->UpdateData(&vertices[0], 2, false);
		myLineVertexBuffer->Bind(0);

		myLineEffect->Bind();
		Engine::GetInstance().GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		aCamera.GetRenderTexture()->Bind(0);
		Engine::GetInstance().GetRenderer().GetContext()->Draw(2, 0);
#endif
	}

	void DebugDrawer::DrawLine(const Camera & aCamera, const LineSegmentShape & aLineToDraw, const Color & aColor /*= Color::White*/)
	{
#ifndef PUBLISH
		DrawLine(aCamera, aLineToDraw.myFirstPosition, aLineToDraw.mySecondPosition, aColor);
#endif
	}

	void DebugDrawer::RenderShape(const Camera & aCamera, const SphereShape & aSphereShape, const Color & aColor)
	{
#ifndef PUBLISH
		RenderSphere(aCamera, aSphereShape.myPosition, aSphereShape.myRadius, aColor);
#endif
	}

	void DebugDrawer::RenderShape(const Camera & aCamera, const LineSegmentShape & aLine, const Color & aColor /*= Vector4f::One*/)
	{
#ifndef PUBLISH
		DrawLine(aCamera, aLine, aColor);
#endif
	}

	void DebugDrawer::RenderShape(const Camera & aCamera, const CapsuleShape & aCapsule, const Color & aColor /*= Vector4f::One*/)
	{
#ifndef PUBLISH
		Vector3f tempSecondPosition = aCapsule.myFirstPosition + aCapsule.myLengthAndDirection;
		Vector3f tempMidPoint = aCapsule.myFirstPosition + (aCapsule.myLengthAndDirection / 2);

		RenderSphere(aCamera, aCapsule.myFirstPosition, aCapsule.myRadius, aColor);
		RenderSphere(aCamera, tempSecondPosition, aCapsule.myRadius, aColor);
		RenderSphere(aCamera, tempMidPoint, aCapsule.myRadius, aColor);

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

		DrawLine(aCamera, capsuleLineEdgeFirstPoint, capsuleLineEdgeSecondPoint, aColor);
		DrawLine(aCamera, aCapsule.myFirstPosition - distanceOffset, tempSecondPosition - distanceOffset, aColor);
#endif
	}

	void DebugDrawer::RenderSphere(const Camera & aCamera, const Vector3f & aPosition, const float aRadius, const Color & aColor)
	{
#ifndef PUBLISH
		RenderSphere(aCamera, aPosition, Vector3f::One * aRadius, aColor);
#endif
	}

	void DebugDrawer::RenderSphere(const Camera & aCamera, const Vector3f & aPosition, const Vector3f &aRadius, const Color & aColor)
	{
#ifndef PUBLISH
		DrawShape(aCamera, mySphereModel, aPosition, aRadius, aColor);
#endif
	}

	void DebugDrawer::RenderCube(const Camera & aCamera, const Vector3f & aCenterPosition, const Vector3f &aSize, const Color & aColor)
	{
#ifndef PUBLISH
		DrawShape(aCamera, myCubeModel, aCenterPosition, aSize, aColor);
#endif
	}

	void DebugDrawer::RenderCube(const Camera & aCamera, const Vector3f & aCenterPosition, const Vector3f &aSize, const Quaternion & aRotation, const Color & aColor /*= Color::White*/)
	{
#ifndef PUBLISH
		DrawShape(aCamera, myCubeModel, aCenterPosition, aSize, aColor, aRotation);
#endif
	}

	void DebugDrawer::DrawCone(const Camera & aCamera, const Vector3f& aFrom, const Vector3f& aDirection, const Color& aColor)
	{
#ifndef PUBLISH
		Quaternion rotation = Quaternion::CreateFromVectors(Vector3f::Zero, aDirection, Vector3f(0.f, 1.f, 0.f));
		rotation.RotateAroundLocalX(-Pi);
		DrawShape(aCamera, myConeModel, aFrom, Vector3f::One, aColor, rotation, false);
#endif
	}

	void DebugDrawer::RenderArrow(const Camera & aCamera, const Vector3f& aFrom, const Vector3f& aTo, const Color& aColor)
	{
#ifndef PUBLISH
		DrawLine(aCamera, aFrom, aTo, aColor);
		Vector3f normal = (aTo - aFrom).GetNormalized();
		DrawCone(aCamera, aTo, normal, aColor);
#endif
	}


	void DebugDrawer::RenderArrow(const Camera & aCamera, const LineSegmentShape & aLineSegment, const Color & aColor)
	{
#ifndef PUBLISH
		RenderArrow(aCamera, aLineSegment.myFirstPosition, aLineSegment.mySecondPosition, aColor);
#endif
	}


	void DebugDrawer::DrawCircle(const GuiRenderTarget & aGUIRenderTarget, const SB::Vector2f aPosition, const float aRadius, const SB::Vector4f aColor /*= SB::Vector4f::One*/)
	{
		

		const float ScaleRadius = aRadius / 256;

		myCircleSprite.SetScale(SB::Vector2f(ScaleRadius, ScaleRadius));
		myCircleSprite.SetOrigin(SB::Vector2f(aRadius, aRadius));
		myCircleSprite.SetColor(aColor);
		myCircleSprite.SetPosition(aPosition);
		aGUIRenderTarget.Render(myCircleSprite);
	}

	void DebugDrawer::DrawShape(const Camera & aCamera, const std::shared_ptr<Model> & aShape, const Vector3f & aPosition, const Vector3f & aScale, const Color & aColor, const Quaternion & aRotation, bool aDrawWireframe)
	{
#ifndef PUBLISH
		if (aDrawWireframe)
		{
			Engine::GetRenderer().EnableWireframe();
		}
		Matrix44f m = SB::Matrix44f::CreateScale(aScale.x * 1.0f, aScale.y * 1.0f, aScale.z * 1.0f) * aRotation.GenerateMatrix() * SB::Matrix44f::CreateTranslation(aPosition);
		aShape->InstantRender(aCamera, aDrawWireframe ? myWireframeEffect : nullptr, m, m, aColor);
		if (aDrawWireframe)
		{
			Engine::GetRenderer().DisableWireframe();
		}
#endif
	}
}

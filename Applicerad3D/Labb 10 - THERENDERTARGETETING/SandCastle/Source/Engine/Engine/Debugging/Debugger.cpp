#include "stdafx.h"
#include "Debugger.h"
#include "Engine\Imgui\imgui_impl_dx11.h"
#include <imgui.h>
#include "Engine\Buffer\VertexBuffer.h"
#include "Engine\Model\AssimpModel.h"
#include "..\Effect\StandardEffect.h"
#include "..\Model\CubeModel.h"

namespace ENGINE_NAMESPACE
{
	Debugger::Debugger(void * aWindowHandle)
	{
		bool initialized = ImGui_ImplDX11_Init(aWindowHandle, Engine::GetInstance().GetRenderer().GetDevice(), Engine::GetInstance().GetRenderer().GetContext());

		myLineEffect = std::make_shared<Effect>();
		myLineEffect->AttachVertexShader("shaders/debugging/line.fx", "VShader");
		myLineEffect->AttachPixelShader("shaders/debugging/line.fx", "PShader");
		InputLayout layout;
		layout.Add("POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		layout.Add("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT);
		myLineEffect->Link(layout);

		myLineVertexBuffer = std::make_shared<VertexBuffer<LineVertex>>(nullptr, 2, false);

		myWireframeEffect = std::make_shared<StandardEffect>("shaders/pbr/vertex.fx", "VShader", "shaders/pbr/wireframe.fx", "PShader");

		mySphereModel = Engine::GetResourceManager().Get<AssimpModel>("models/lightspheres/lightsphere_1.fbx");
		myCubeModel = std::make_shared<CubeModel>(nullptr);
	}

	void Debugger::DrawLine(const Vector3f & aFrom, const Vector3f & aTo, const Vector4f & aColor)
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

	void Debugger::RenderShape(const SphereShape & aSphereShape, const Vector4f & aColor)
	{
		RenderSphere(aSphereShape.myPosition, aSphereShape.myRadius, aColor);
	}

	void Debugger::RenderSphere(const Vector3f & aPosition, const float aRadius, const Vector4f & aColor)
	{
		RenderSphere(aPosition, Vector3f::One * aRadius, aColor);
	}

	void Debugger::RenderSphere(const Vector3f & aPosition, const Vector3f &aRadius, const Vector4f & aColor)
	{
		DrawShape(mySphereModel, aPosition, aRadius, aColor);
	}

	void Debugger::RenderCube(const Vector3f & aCenterPosition, const Vector3f &aSize, const Vector4f & aColor)
	{
		DrawShape(myCubeModel, aCenterPosition, aSize, aColor);
	}

	void Debugger::DrawShape(const std::shared_ptr<Model> & aShape, const Vector3f & aPosition, const Vector3f & aScale, const Vector4f & aColor)
	{
		Engine::GetRenderer().EnableWireframe();
		aShape->InstantRender(myWireframeEffect, SB::Matrix44f::CreateScale(aScale.x * 1.0f, aScale.y * 1.0f, aScale.z * 1.0f) * SB::Matrix44f::CreateTranslation(aPosition), aColor);
		Engine::GetRenderer().DisableWireframe();
	}

	Debugger::~Debugger()
	{
		ImGui_ImplDX11_Shutdown();
	}

	void Debugger::NewFrame()
	{
		ImGui_ImplDX11_NewFrame();
	}

	void Debugger::RenderFrame()
	{
		ImGui::Render();
	}
}

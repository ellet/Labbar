#include "stdafx.h"
#include <imgui.h>
#include "Debugger.h"
#include "Engine\Imgui\imgui_impl_dx11.h"
#include "Engine\Component\Collider\RenderColliderComponent.h"
#include "Engine\GenericEngineMessages.h"
#include "DebugFunctions\DebugRegristry.h"
#include "DebugFunctions\DebugToggleFunction.h"
#include "DebugGUI\DebuggerGUI.h"
#include "Engine\Window\Cursor\Cursor.h"
#include "..\..\..\Game\Game\Scene\MainMenuScene.h"
#include "..\Scene\Messages\PushSceneMessage.h"


namespace ENGINE_NAMESPACE
{
	Debugger::Debugger(void * aWindowHandle, const Cursor & aCursor) : myCursor(&aCursor)
	{
		bool initialized = ImGui_ImplDX11_Init(aWindowHandle, Engine::GetInstance().GetRenderer().GetDevice(), Engine::GetInstance().GetRenderer().GetContext());

		myIsDebuging = false;
		myPausSceneUpdate = false;

		myDebugFeatures.Resize(static_cast<unsigned short>(DebugFunctionsEnumList::enumLength));
		RegisterInternalFunctions();

		myDebugWindowsFlags.Resize(static_cast<unsigned short>(DebugWindowEnum::enumlength), false);
	}

	void Debugger::Update()
	{
		for (unsigned short iFeature = 0; iFeature < myDebugFeatures.Size(); ++iFeature)
		{
			const KeyboardKey tempKey = myDebugFeatures[iFeature]->GetKeyTypeForPress();
			if (tempKey != KeyboardKey::eNone && myInputListener.GetPressedThisFrame(tempKey) == true)
			{
				myDebugFeatures[iFeature]->TriggerOnPressed();
			}
		}

		if (myIsDebuging == true)
		{
			DebugGUI::ShowMainGUI(myDebugWindowsFlags);

			if (GetWindowStatus(DebugWindowEnum::eDebugToggle) == true)
			{
				DebugGUI::ShowTogglesWindow(myDebugFeatures, myDebugWindowsFlags[static_cast<unsigned short>(DebugWindowEnum::eDebugToggle)]);
			}

			if (GetWindowStatus(DebugWindowEnum::eSceneWindow) == true)
			{
				DebugGUI::ShowSceneSelectWindow(myScenes, myPopCurrentScene, myDebugWindowsFlags[static_cast<unsigned short>(DebugWindowEnum::eSceneWindow)]);
			}
		}
	}

	bool Debugger::GetDebugState()
	{
		return myIsDebuging;
	}

	bool Debugger::CheckIfPaused()
	{
		return myPausSceneUpdate;
	}

	void Debugger::LoadSceneAtIndex(const unsigned short aIndex)
	{
		PostMaster::Post(PushSceneMessage(myScenes[aIndex], eSceneType::eMajor));
	}

	void Debugger::AddDebugFeature(DebugToggleFunction & aFunction)
	{
		myDebugFeatures[static_cast<unsigned short>(aFunction.GetFeatureType())] = &aFunction;
	}

	void Debugger::AddSceneForSceneSelection(std::shared_ptr<Scene> aScene)
	{
		myScenes.Add(aScene);
	}

	ReceiveResult Debugger::Receive(const PopSceneMessage & aMessage)
	{
		myPopCurrentScene = false;
		return ReceiveResult::eContinue;
	}

	bool Debugger::GetWindowStatus(const DebugWindowEnum aWindowID)
	{
		return myDebugWindowsFlags[static_cast<unsigned short>(aWindowID)];
	}

	void Debugger::TriggerDebugFunction(const DebugFunctionsEnumList aFunctionSlot)
	{
		myDebugFeatures[static_cast<unsigned short>(aFunctionSlot)]->TriggerOnPressed();
	}

	void Debugger::RegisterInternalFunctions()
	{
		DebugToggleFunction * tempFunction = new DebugToggleFunction("Debug Toggle", DebugFunctionsEnumList::eDebugMode,
			[&]()
		{
			myIsDebuging = !myIsDebuging;
			myPausSceneUpdate = myIsDebuging;
			PostMaster::Post<ShowCursorMessage>(ShowCursorMessage(myIsDebuging));
			PostMaster::Post<ConfineMouseMessage>(ConfineMouseMessage(!myIsDebuging));
		},
		KeyboardKey::eF2
		);
		AddDebugFeature(*tempFunction);

		DebugToggleFunction * temppauseFunction = new DebugToggleFunction("GamePauseToggle", DebugFunctionsEnumList::eGamePause,
			[&]()
		{
			myPausSceneUpdate = !myPausSceneUpdate;
		},
		KeyboardKey::eP
		);
		AddDebugFeature(*temppauseFunction);

		DebugToggleFunction * tempSwitchMouse = new DebugToggleFunction("ShowMouseToggle", DebugFunctionsEnumList::eMouseToggle,
			[&]()
		{
			PostMaster::Post<ShowCursorMessage>(ShowCursorMessage(myCursor->IsHidden()));
		},
		KeyboardKey::eF1
		);
		AddDebugFeature(*tempSwitchMouse);
	}

	Debugger::~Debugger()
	{
		ImGui_ImplDX11_Shutdown();
		myDebugFeatures.DeleteAll();
	}

	void Debugger::Shutdown()
	{
		myScenes.RemoveAll();
	}

	void Debugger::Initialize()
	{
		DebugFunctions::RegisterFunctions();
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

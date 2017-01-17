#pragma once

#include "Engine\Input\InputListener.h"
#include "Engine/Debugging/DebugDrawer.h"
#include "Engine/Debugging/DebugFunctionsEnumList.h"
#include "Engine/Debugging/DebugWindowsEnum.h"


namespace SB
{
	class DebugToggleFunction;
	class Cursor;
	struct PopSceneMessage;

	class Debugger : public Subscriber<PopSceneMessage>
	{
	public:
		Debugger(void * aWindowHandle, const Cursor & aCursor);
		~Debugger();

		void Shutdown();

		void Initialize();

		void NewFrame();
		void RenderFrame();
		void Update();

		bool GetDebugState();
		bool CheckIfPaused();
		
		void LoadSceneAtIndex(const unsigned short aIndex);
		void TriggerDebugFunction(const DebugFunctionsEnumList aFunctionSlot);

		void AddDebugFeature(DebugToggleFunction & aFunction);
		void AddSceneForSceneSelection(std::shared_ptr<Scene> aScene);
		
		void PreRenderDebugSettings();
		void AfterRenderDebugSettings();

		DebugDrawer & GetDebugDrawer()
		{ return myDebugDrawer;}


		virtual ReceiveResult Receive(const PopSceneMessage & aMessage) override;

	private:
		bool GetWindowStatus(const DebugWindowEnum aWindowID);

		void RegisterInternalFunctions();

		InputListener myInputListener;
		bool myIsDebuging;
		bool myPausSceneUpdate;
		bool myRenderAsWireFrames;

		WindowFlagsList myDebugWindowsFlags;
		GrowingArray<DebugToggleFunction*> myDebugFeatures;
		GrowingArray<std::shared_ptr<Scene>> myScenes;
		bool myPopCurrentScene;

		const Cursor * myCursor;

		DebugDrawer myDebugDrawer;
	};
}


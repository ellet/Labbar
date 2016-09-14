#pragma once

#include "CU/Input/InputWrapper/InputWrapper.h"
#include "CU\Systems\Timer\TimeManager.h"

namespace CommonUtilities
{

	class MainSingleton
	{
	public:
		static void Create();

		static void Destroy();

		template<typename RendererClass>
		static RendererClass & GetRenderer();

		static InputWrapper & GetInputWrapper();
		static TimeManager & GetTimerManager();

		static const Time & GetDeltaTime();

	private:
		MainSingleton(); 
		~MainSingleton();
		
		static MainSingleton & GetInstance();
		static MainSingleton * ourInstance;

		TimeManager myTimeManager;
		InputWrapper myInputWrapper;

	};

	template<typename RendererClass>
	RendererClass & CommonUtilities::MainSingleton::GetRenderer()
	{
		RendererClass * renderer = dynamic_cast<RendererClass*>(GetInstance().myRenderer);
		DL_ASSERT(renderer != nullptr, "Tried to Get Renderer with wrong template argument! USE A RENDERER!!");
		return *renderer;
	}

}

#define GET_INPUT CU::MainSingleton::GetInputWrapper()
#define GET_DELTA_TIME CU::MainSingleton::GetDeltaTime();
#define GET_DELTA_SECONDS CU::MainSingleton::GetDeltaTime().GetSeconds();
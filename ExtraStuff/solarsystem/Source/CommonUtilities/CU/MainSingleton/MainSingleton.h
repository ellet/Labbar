#pragma once

#include "CU/InputWrapper/InputWrapper.h"
#include "CU/PostMaster/PostMaster.h"

namespace CommonUtilities
{
	class BaseRenderer;
	class BaseCreationManager;

	class MainSingleton
	{
	public:
		static void Create();

		static void Destroy();

		template<typename RendererClass>
		static RendererClass & GetRenderer();

		static InputWrapper & GetInputWrapper();

		static PostMaster & GetPostMaster();

		static void SetRenderer(BaseRenderer * aRenderer);

	private:
		MainSingleton(); 
		~MainSingleton();
		
		static MainSingleton & GetInstance();
		static MainSingleton * ourInstance;

		BaseRenderer * myRenderer;

		InputWrapper myInputWrapper;
		PostMaster myPostMaster;

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
#define GET_POSTMASTER CU::MainSingleton::GetPostMaster();
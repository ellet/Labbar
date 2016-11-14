#include "stdafx.h"
#include "PostMaster.h"

namespace ENGINE_NAMESPACE
{
	Stack<PostMasterState*> PostMaster::ourStateStack;
	std::atomic<unsigned short> PostMaster::ourNextStateIndex = 0;
	std::unique_ptr<PostMasterStateBinding> PostMaster::ourGlobalStateBinding;
	PostMasterState PostMaster::ourGlobalState;

	void PostMaster::Initialize()
	{
		ourGlobalStateBinding = std::unique_ptr<PostMasterStateBinding>(new PostMasterStateBinding(Push(ourGlobalState)));
	}

	void PostMaster::Shutdown()
	{
		ourGlobalStateBinding = nullptr;
		ourGlobalState = PostMasterState();
	}

	PostMasterState::PostMasterState()
	{
		myStateIndex = 0;
	}

	PostMasterState::~PostMasterState()
	{
		for (unsigned short i=0; i<myRemovers.Size(); i++)
		{
			(*myRemovers[i])();
			delete myRemovers[i];
		}
	}

	void PostMasterState::AddRemover(const std::function<void()>& aRemover)
	{
		myRemovers.Add(new std::function<void()>(aRemover));
	}

	PostMasterStateBinding PostMaster::Push(PostMasterState& aState)
	{
		if (aState.myStateIndex == 0)
		{
			aState.myStateIndex = ourNextStateIndex.fetch_add(1);
			if (aState.myStateIndex >= 30000)
			{
				Error("PostMaster states are getting really large, go scream at a programmer to stop creating so many states!");
			}
		}
		ourStateStack.Push(&aState);

		return PostMasterStateBinding();
	}

	void PostMaster::Pop()
	{
		ourStateStack.Pop();
	}

	PostMasterState& PostMaster::GetCurrentState()
	{
		return *ourStateStack.Top();
	}

	void PostMaster::AssertState(const PostMasterState& aState)
	{
		if (&GetCurrentState() != &aState)
		{
			Error("Invalid PostMaster state!");
		}
	}

	PostMasterState& PostMaster::GetGlobalState()
	{
		return ourGlobalState;
	}
}

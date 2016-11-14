#include "stdafx.h"
#include "DialogChain.h"
#include "DialogNode.h"
#include "Engine/SoundManager/SoundManager.h"


DialogChain::DialogChain()
{
	myCurrentPlayingNode = 0;
	myIsDone = false;
	myOnCompleteFunction = nullptr;
}

DialogChain::DialogChain(SB::DataNode aData, const std::function<void()>& aOnCompleteFunction)
{
	myCurrentPlayingNode = 0;
	myIsDone = false;
	myOnCompleteFunction = aOnCompleteFunction;

	LoadData(aData);

	myVoiceID = SB::Engine::GetSoundManager().RegisterObjectAtFreeID();
}

DialogChain::~DialogChain()
{
}


void DialogChain::Start()
{
	if (myDialogNodes.Size() == 0)
	{
		myIsDone = true;
		return;
	}

	Reset();
	myDialogNodes[myCurrentPlayingNode]->Start();
}

void DialogChain::Reset()
{
	myCurrentPlayingNode = 0;
	myIsDone = false;
	SB::Engine::GetSoundManager().PostEvent("Stop_All_Voice", myVoiceID);

	for(unsigned short i = 0; i < myDialogNodes.Size(); ++i)
	{
		myDialogNodes[i]->Reset();
	}
}

void DialogChain::Update(const SB::Time& aDeltaTime)
{
	if (myIsDone == true)
	{
		return;
	}

	myDialogNodes[myCurrentPlayingNode]->Update(aDeltaTime);

	if (myDialogNodes[myCurrentPlayingNode]->GetIsDonePlaying() == true)
	{
		AdvanceToNextDialogNode();
	}
}

void DialogChain::Render() const
{
	if (myIsDone == true)
	{
		return;
	}

	if (myDialogNodes[myCurrentPlayingNode]->GetIsDonePlaying() == false)
	{
		myDialogNodes[myCurrentPlayingNode]->Render();
	}
}

void DialogChain::LoadData(SB::DataNode aData)
{
	for(unsigned short i = 0; i < aData["dialogNodes"].Capacity(); ++i)
	{
		myDialogNodes.Add(std::make_shared<DialogNode>(aData["dialogNodes"][i]));
	}
}

void DialogChain::AddDialogNode(std::shared_ptr<DialogNode> aNode)
{
	myDialogNodes.Add(aNode);
}

//Returns true if there is another dialog node to advance to
bool DialogChain::AdvanceToNextDialogNode()
{
	++myCurrentPlayingNode;

	if (myCurrentPlayingNode >= myDialogNodes.Size())
	{
		myIsDone = true;

		if (myOnCompleteFunction != nullptr)
		{
			myOnCompleteFunction();
		}

		return false;
	}

	myDialogNodes[myCurrentPlayingNode]->Start();
	return true;
}

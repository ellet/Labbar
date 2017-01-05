#include "stdafx.h"
#include "WaveManagerComponent.h"
#include "Game/Waves/Wave.h"


WaveManagerComponent::WaveManagerComponent()
{
	myWaves.Reserve(10);
	mySpawnPoints.Reserve(4);
	myCurrentWave = 0;
	myIsCompleted = false;
}

WaveManagerComponent::~WaveManagerComponent()
{
}

void WaveManagerComponent::Initialize()
{
	myWaveFeedbackText.SetPositionTopLeft(SB::Vector2f(30.0f, 30.f));
	myWaveFeedbackText.SetColor(SB::Vector4f(1.f, 1.f, 0.f, 1.f));
	myWaveFeedbackText.SetFont(SB::Engine::GetResourceManager().Get<SB::Font>("Assets/Text/Calibri"));
	myWaveFeedbackText.SetText(DetermineWaveFeedbackText());
}

void WaveManagerComponent::Update(const SB::Time& aDeltaTime)
{
	if (myIsCompleted == true)
	{
		return;
	}

	if (myWaves.Empty() == true)
	{
		TriggerArenaCompletion();
		return;
	}

	myWaves[myCurrentWave]->Update(aDeltaTime);

	if (myWaves[myCurrentWave]->GetHasEnemiesRemaining() == false)
	{
		AdvanceToNextWave();
	}
}

void WaveManagerComponent::Render(const SB::Camera& aCamera) const
{
	myWaveFeedbackText.Render(*myObject->GetScene().GetGUIRenderTarget());
}


void WaveManagerComponent::LoadData(SB::DataNode aProperties)
{
	for(unsigned short i = 0; i < aProperties["waves"].Capacity(); ++i)
	{
		myWaves.Add(std::make_shared<Wave>(aProperties["waves"][i]));
	}

	if (aProperties.HasMember("currentWave") == true)
		myCurrentWave = aProperties["currentWave"].GetUShort();
	else
		myCurrentWave = 0;

	if (aProperties.HasMember("isCompleted") == true)
		myIsCompleted = aProperties["isCompleted"].GetBool();
	else
		myIsCompleted = false;
}

void WaveManagerComponent::ToJson(SB::JsonSerializer& aSerializer) const
{
	aSerializer.WriteNode("type", "WaveManagerComponent");

	aSerializer.WriteObject("properties");
	aSerializer.WriteArray("waves");
	for(unsigned short i = 0; i < myWaves.Size(); ++i)
	{
		aSerializer.WriteObject();
		myWaves[i]->ToJson(aSerializer);
		aSerializer.StepOut();
	}
	aSerializer.StepOut();
	aSerializer.WriteNode("currentWave", myCurrentWave);
	aSerializer.WriteNode("isCompleted", myIsCompleted);
	aSerializer.StepOut();
}

SB::ReceiveResult WaveManagerComponent::Receive(const ActivateSpawnPointMessage& aMessage)
{
	mySpawnPoints.Add(aMessage.spawnPoint);
	return SB::ReceiveResult::eContinue;
}


//PRIVATE FUNCTIONS:

void WaveManagerComponent::AdvanceToNextWave()
{
	++myCurrentWave;
	myWaveFeedbackText.SetText(DetermineWaveFeedbackText());

#ifdef _DEBUG
	std::cout << std::endl << "Advancing to wave: " << myCurrentWave << std::endl;
#endif

	if (myCurrentWave >= myWaves.Size())
	{
		TriggerArenaCompletion();
	}
}

void WaveManagerComponent::TriggerArenaCompletion()
{
	//TODO: Go back to arena selection, unlocking the next arena

#ifdef _DEBUG
	std::cout << std::endl << "Arena Completed!" << std::endl;
#endif

	myWaveFeedbackText.SetText("Arena completed!");
	myWaveFeedbackText.SetColor(SB::Vector4f(1.f, 1.f, 1.f, 1.f));
	myIsCompleted = true;
}

std::string WaveManagerComponent::DetermineWaveFeedbackText() const
{
	std::string text = "Wave: " + std::to_string(myCurrentWave + 1) + "/" + std::to_string(myWaves.Size());
	return text;
}

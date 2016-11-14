#include "stdafx.h"
#include "StreakComponent.h"
#include "Engine/Buffer/VertexBuffer.h"
#include "Engine/Streak/StreakEffect.h"
#include "Engine/Streak/StreakData.h"
#include "Engine/GameObject/GameObject.h"
#include <D3D11.h>
#include "Engine/Text/Text.h"
#include "Engine/Camera/Camera.h"
#include "StreakLogic.h"

namespace
	ENGINE_NAMESPACE
{
	void StreakComponent::Initialize()
	{
		if (myIsSetup == false)
		{
			Error("Not set up!");
		}

		myStreakVertices.Resize(static_cast<unsigned short>(myNumberOfSegments + 3));
		myStreakAge.Resize(myStreakVertices.Size());
		memset(&myStreakVertices[0], 0, sizeof(myStreakVertices[0]) * myStreakVertices.Size());

		myVertexBuffer = std::make_shared<VertexBuffer<StreakData>>(&myStreakVertices[0], myStreakVertices.Size(), false);

		myEffect = std::make_shared<StreakEffect>();
		myIsFilled = false;

		for (unsigned short i = 0; i < myStreakVertices.Size(); i++)
		{
			myStreakAge[i] = 0.f;
			myStreakVertices[i].mySize = 0.f;
		}

		myCurrentIndex = 0;
		SpawnStreak();
		SpawnStreak();


		GetCurrentPoint().myPosition = myObject->GetTransformation().GetPosition();
		myStartPosition = GetCurrentPoint().myPosition;

		// myText = std::make_shared<Text>();
	}

	StreakComponent::StreakComponent()
	{
		myIsSetup = false;
	}

	StreakComponent::~StreakComponent()
	{
	}

	void StreakComponent::Update(const Time& aDeltaTime)
	{
		Vector3f previousPosition = GetBackwardPoint().myPosition;

		SB::Vector3f objectPosition = myObject->GetTransformation().GetPosition();

		GetCurrentPoint().myPosition = objectPosition;

		SB::Vector3f projectionForwardAmount = (objectPosition - previousPosition).GetNormalized() * 0.01f;
		GetHeadingPoint().myPosition = objectPosition + projectionForwardAmount;

		travelledTime += aDeltaTime;
		float travelledProgress = travelledTime.InSeconds() / myTimeBetweenStreakSegments.InSeconds();
		if (travelledProgress >= 1.f)
		{
			SpawnStreak();
			GetCurrentPoint().myPosition = objectPosition + projectionForwardAmount * 0.5f;
			GetHeadingPoint().myPosition = GetCurrentPoint().myPosition + projectionForwardAmount;
			travelledTime = 0.f;
		}
		else
		{
			StreakData & trailingForward = GetSegment(3);
			const StreakData & trailingForward2 = GetSegment(4);
			trailingForward.myPosition = myTrailingForwardPos + myTrailingForwardVector * travelledProgress;

			GetTrailingPoint().myPosition = trailingForward.myPosition + (trailingForward.myPosition - trailingForward2.myPosition).GetNormalized() * 0.1f;
		}

		if (myIsFilled == false && myCurrentIndex == 2)
		{
			// Project backwards during first actual segment. Move the movement from 0-1 to 1-2
			myStreakVertices[2].myPosition = objectPosition;
			myStreakVertices[1].myPosition = myStartPosition;
			myStreakVertices[0].myPosition = (myStartPosition - projectionForwardAmount);
			//Project forward for first segment
			//myStreakVertices[3].myPosition = myStreakVertices[2].myPosition + ((myStreakVertices[1].myPosition - myStreakVertices[2].myPosition).GetNormalized() * 0.01f);
		}

		float totalAge = myTimeBetweenStreakSegments.InSeconds() * static_cast<float>(myNumberOfSegments);
		for (unsigned short i = 0; i < myStreakVertices.Size(); i++)
		{
			myStreakAge[i] += aDeltaTime;
			myStreakVertices[i].myColor = myStreakLogic->CalculateColor(myStreakAge[i].InSeconds() / totalAge);
			myStreakVertices[i].mySize = myStreakLogic->CalculateSize(myStreakAge[i].InSeconds() / totalAge);
		}
	}

	void StreakComponent::Render() const
	{
		if (myIsFilled || myCurrentIndex + 1 == myStreakVertices.Size())
		{
			myVertexBuffer->UpdateData(&myStreakVertices[0], myStreakVertices.Size(), false, GetSegmentIndex(2));

			myVertexBuffer->Bind(0);
			myEffect->Bind();

			Engine::GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ);
			Engine::GetRenderer().GetContext()->Draw(myStreakVertices.Size(), 0);
		}
		else
		{
			myVertexBuffer->UpdateData(&myStreakVertices[0], myStreakVertices.Size(), false, 0);

			myVertexBuffer->Bind(0);
			myEffect->Bind();

			Engine::GetRenderer().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ);
			Engine::GetRenderer().GetContext()->Draw(myCurrentIndex + 2, 0);
		}

		// for (int i=0; i<myStreakVertices.Size(); i++)
		// {
		// 	Vector2f pos = myObject->GetScene().GetCamera().WorldToScreen(myStreakVertices[static_cast<unsigned short>(i)].myPosition);
		// 	pos += Vector2f::One;
		// 	pos /= 2.f;
		// 	pos.y = 1.f - pos.y;
		// 	pos *= Engine::GetRenderer().GetRenderTargetResolution();
		// 	
		// 	myText->SetPositionTopLeft(pos);
		// 	myText->SetText(std::to_string(i));
		// 	myText->Render();
		// }
	}

	void StreakComponent::LoadData(DataNode aProperties)
	{
		StreakLogic * streakLogic = new UnityStreakLogic(aProperties);
		int numberOfSegments = aProperties["numberOfSegments"].GetInt();
		float timePerSegment = aProperties["streakTime"].GetFloat() / static_cast<float>(numberOfSegments);
		Setup(streakLogic, timePerSegment, numberOfSegments);
	}
	void StreakComponent::ToJson() const
	{
		if (myShouldBeSaved == false)
		{
			return;
		}
		JsonSerializer &serializer = Engine::GetJsonSerializer();
		serializer.WriteObject("properties");
		myStreakLogic->SaveToJson();
		serializer.WriteNode("numberOfSegments", myNumberOfSegments);
		serializer.WriteNode("streakTime", myTimeBetweenStreakSegments.InSeconds());
		serializer.StepOut();
		serializer.WriteNode("type", "StreakComponent");
	}

	void StreakComponent::Setup(StreakLogic * aStreakLogic, const Time & aTimeBetweenStreakSegments, int aNumberOfStreakSegments)
	{
		myStreakLogic = std::unique_ptr<StreakLogic>(aStreakLogic);
		myTimeBetweenStreakSegments = aTimeBetweenStreakSegments;
		myNumberOfSegments = aNumberOfStreakSegments;

		myIsSetup = true;
	}



	void StreakComponent::SpawnStreak()
	{
		StreakData tempData;
		tempData.myPosition = myObject->GetTransformation().GetPosition();
		tempData.myColor = myStreakLogic->CalculateColor(0.f);
		tempData.mySize = myStreakLogic->CalculateSize(0.f);

		myStreakVertices[myCurrentIndex] = tempData;
		myStreakAge[myCurrentIndex] = 0.f;
		myStreakAge[(myCurrentIndex + 1) % myStreakAge.Size()] = 0.f;

		++myCurrentIndex;

		if (myCurrentIndex >= myStreakVertices.Size())
		{
			myCurrentIndex = 0;
			myIsFilled = true;
		}

		StreakData & trailingForward = GetSegment(3);
		const StreakData & trailingForward2 = GetSegment(4);

		myTrailingForwardPos = trailingForward.myPosition;
		myTrailingForwardVector = trailingForward2.myPosition - trailingForward.myPosition;
	}

	StreakData & StreakComponent::GetTrailingPoint()
	{
		return myStreakVertices[(myCurrentIndex + 2) % myStreakVertices.Size()];
	}

	StreakData& StreakComponent::GetSegment(int aRelativeIndexToCurrent)
	{
		return myStreakVertices[GetSegmentIndex(aRelativeIndexToCurrent)];
	}

	unsigned short StreakComponent::GetSegmentIndex(int aRelativeIndexToCurrent) const
	{
		int index = myCurrentIndex + aRelativeIndexToCurrent;
		if (index < 0)
		{
			return static_cast<unsigned short>(myStreakVertices.Size() + index);
		}
		if (index >= myStreakVertices.Size())
		{
			return static_cast<unsigned short>(index - myStreakVertices.Size());
		}
		return static_cast<unsigned short>(index);
	}

	StreakData & StreakComponent::GetBackwardPoint()
	{
		if (myCurrentIndex == 0)
			return myStreakVertices[myStreakVertices.Size() - 1];
		return myStreakVertices[myCurrentIndex - 1];
	}

	StreakData & StreakComponent::GetCurrentPoint()
	{
		return myStreakVertices[myCurrentIndex];
	}

	StreakData & StreakComponent::GetHeadingPoint()
	{
		if (myCurrentIndex + 1 == myStreakVertices.Size())
			return myStreakVertices[0];
		return myStreakVertices[myCurrentIndex + 1];
	}
}

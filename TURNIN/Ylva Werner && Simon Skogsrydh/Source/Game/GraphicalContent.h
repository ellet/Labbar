#pragma once

#include "WrappedSprite.h"
#include <DLDebug/DL_Debug.h>
#include <Intersection/Intersection2D.h>

namespace DX2D
{
	class CSprite;
}

class GraphicalContent
{
public:
	GraphicalContent()
	{}
	GraphicalContent(const size_t aNodeID) : myNodeID(aNodeID)
	{
		myNodeSprite.Init();
		myIsPathFlag = false;
		myWasUpdateFlag = false;
		myIsBlockedFlag = false;
		myCollider.myRadius = 32.f;
	}
	~GraphicalContent();

	void ConfirmID(const size_t & aID)
	{
		DL_ASSERT(myNodeID == aID, "Graphical node ID is not same as NODEID");
	}

	WrappedSprite & GetSprite();

	void SetPosition(const Vector2f & aPosition)
	{
		myNodeSprite.SetPosition(aPosition);
		myCollider.ChangePosition(aPosition);
	}

	Vector2f GetPosition()
	{
		return myNodeSprite.GetPosition();
	}

	size_t GetNodeID();

	void SetPathLinkID(const size_t aID)
	{
		myPathLink = aID;
	}

	size_t GetPathLinkID()
	{
		return myPathLink;
	}

	bool CheckIfPath()
	{
		return myIsPathFlag;
	}

	void IsPath()
	{
		myNodeSprite.SetColor(Vector4f(1.f, 0.f, 0.f, 1.f));
		myIsPathFlag = true;
	}

	void IsStart()
	{
		myNodeSprite.SetColor(Vector4f(0.5f, 0.f, 1.f, 1.f));
		myIsPathFlag = true;
	}

	void IsGoal()
	{
		myNodeSprite.SetColor(Vector4f(0.5f, 0.5f, 0.f, 1.f));
		myIsPathFlag = true;
	}

	void SwitchBlocked(bool aIsBlocked)
	{
		myIsBlockedFlag = aIsBlocked;
		if (aIsBlocked == true)
		{
			myNodeSprite.SetColor(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			myNodeSprite.SetColor(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
		}
		
	}

	void WasUpdated()
	{
		myNodeSprite.SetColor(Vector4f(1.f, 0.f, 0.f, 1.f));
		myWasUpdateFlag = true;
	}

	void ResetPath()
	{
		myPathLink = SIZE_MAX;
		if (myIsBlockedFlag == false)
		{
			myNodeSprite.SetColor(Vector4f::One);
		}
		myIsPathFlag = false;
		myWasUpdateFlag = false;
	}
	
	bool CheckIfUpdated()
	{
		return myWasUpdateFlag;
	}

	const Intersection2D::Circle2D & GetCollider()
	{
		return myCollider;
	}
	
private:
	Intersection2D::Circle2D myCollider;
	bool myIsBlockedFlag;
	bool myIsPathFlag;
	bool myWasUpdateFlag;
	WrappedSprite myNodeSprite;
	size_t myNodeID;
	size_t myPathLink;
};

inline WrappedSprite & GraphicalContent::GetSprite()
{
	return myNodeSprite;
}

inline size_t GraphicalContent::GetNodeID()
{
	return myNodeID;
}
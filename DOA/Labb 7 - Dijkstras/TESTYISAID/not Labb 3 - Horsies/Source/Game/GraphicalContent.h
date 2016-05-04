#pragma once

#include "WrappedSprite.h"
#include <DLDebug/DL_Debug.h>

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
		myIsDirty = true;
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

	void LinkReset()
	{
		myIsDirty = true;
	}

	void SetLinkDrawn()
	{
		myIsDirty = false;
	}

	bool GetHasNotDrawnLinks()
	{
		return myIsDirty;
	}

	void IsPath()
	{
		myNodeSprite.SetColor(Vector4f(1.f, 0.f, 0.f, 1.f));
	}

	void ResetPath()
	{
		myPathLink = SIZE_MAX;
		myNodeSprite.SetColor(Vector4f::One);
	}


private:
	bool myIsDirty;
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
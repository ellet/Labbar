#include "stdafx.h"
#include "PartionGrid.h"
#include <limits>
#include <math.h>


const unsigned short Rows = 20;
const unsigned short Columns = 20;

PartionGrid::PartionGrid()
	: myTiles(20, 20, true)
{
}


PartionGrid::~PartionGrid()
{
}

void PartionGrid::Init(const CU::GrowingArray<CU::Vector2f> & aCirclePositions)
{
	myPointOfView.Init();

	myCircles.Init(aCirclePositions.Size());
	myCircles.Resize(aCirclePositions.Size());
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&Tile::Init));


	for (unsigned short iY = 0; iY < Rows; ++iY)
	{
		for (unsigned short iX = 0; iX < Columns; ++iX)
		{
			myTiles.Access(iX, iY).SetPosition(CU::Vector2f(static_cast<float>(iX * 40), static_cast<float>(iY * 40)));
		}
	}

	for (unsigned short iCircle = 0; iCircle < aCirclePositions.Size(); ++iCircle)
	{
		myCircles[iCircle].Init(aCirclePositions[iCircle]);
	}

	AssignCirclesToTiles();
}

void PartionGrid::Update()
{
	myPointOfView.Update();
	myCircles.CallFunctionOnAllMembers(std::mem_fn(&Circle::Update));
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&Tile::Reset));


	CollisionTest();
}

void PartionGrid::Draw() const
{
	myPointOfView.Draw();
	myCircles.CallFunctionOnAllMembers(std::mem_fn(&Circle::Draw));
	myTiles.CallFunctionOnAllMembers(std::mem_fn(&Tile::Draw));
}

void PartionGrid::SetPointOfViewPosition(const CU::Vector2f & aPosition)
{ 
	myPointOfView.SetPosition(aPosition);
}

void PartionGrid::CollisionTest()
{
	for (unsigned short iY = 0; iY < Rows; ++iY)
	{
		for (unsigned short iX = 0; iX < Columns; ++iX)
		{
			if (myTiles.Access(iX, iY).CollisionTest(myPointOfView) == true)
			{
				if (RaySight(CU::Vector2f(static_cast<float>(iX) * 40.f, static_cast<float>(iY) * 40), myPointOfView.GetCircle().myMainPoint) == false)
				{
					myTiles.Access(iX, iY).SetToSeen();
				}
				if (myTiles.Access(iX, iY).GetObjectOnTop() != nullptr)
				{
					if (CircleIsVisible(*myTiles.Access(iX, iY).GetObjectOnTop(), myPointOfView.GetCircle().myMainPoint) == true)
					{
						if (myTiles.Access(iX, iY).GetObjectOnTop()->CollisionTest(myPointOfView) == true)
						{
							//RenderConverter::DrawLine(myTiles.Access(iX, iY).GetObjectOnTop()->GetPosition(), myPointOfView.GetCircle().myMainPoint);
							myTiles.Access(iX, iY).GetObjectOnTop()->SetIsSeen();
						}
					}
				}
			}
		}
	}
}


bool PartionGrid::CircleIsVisible(Circle & aCircle, const CU::Vector2f & aPoVPosition)
{
	Intersection2D::LineSegment2D distanceToPoV(aCircle.GetPosition(), aPoVPosition);
	CU::Vector2f diameterNormal = distanceToPoV.GetNormal() * 25.f;

	CU::Vector2f circleLeftCorner = aCircle.GetPosition() - diameterNormal;
	CU::Vector2f circleRightCorner = aCircle.GetPosition() + diameterNormal;

	bool result = false;

	if (RaySight(aCircle.GetPosition(), aPoVPosition) == false)
	{
		//RenderConverter::DrawLine(aCircle.GetPosition(), aPoVPosition);
		return true;//result = true;
	}
	/*else
	{
		RenderConverter::DrawLine(aCircle.GetPosition(), aPoVPosition, CU::Vector4f(1.f, 0.f, 0.f, 1.f));
	}*/

	if (RaySight(circleLeftCorner, aPoVPosition) == false)
	{
		//RenderConverter::DrawLine(circleLeftCorner, aPoVPosition);
		return true;//result = true;
	}
	/*else
	{
		RenderConverter::DrawLine(circleLeftCorner, aPoVPosition, CU::Vector4f(1.f, 0.f, 0.f, 1.f));
	}*/

	if (RaySight(circleRightCorner, aPoVPosition) == false)
	{
		//RenderConverter::DrawLine(circleRightCorner, aPoVPosition);
		return true;//result = true;
	}
	//else
	//{
	//	RenderConverter::DrawLine(circleRightCorner, aPoVPosition, CU::Vector4f(1.f, 0.f, 0.f, 1.f));
	//}

	return result;
}

bool PartionGrid::RaySight(const CU::Vector2f & aCirclePosition, const CU::Vector2f & aPoVPosition)
{
#pragma region ugly stolen code

	Intersection2D::LineSegment2D rayTrace(aCirclePosition, aPoVPosition);

	float x0 = aCirclePosition.x / 40;
	float y0 = aCirclePosition.y / 40;
	float x1 = aPoVPosition.x / 40;
	float y1 = aPoVPosition.y / 40;

	float dx = fabs(x1 - x0);
	float dy = fabs(y1 - y0);

	int x = int(floor(x0));
	int y = int(floor(y0));

	int n = 1;
	int x_inc, y_inc;
	float error;

	if (dx == 0)
	{
		x_inc = 0;
		error = std::numeric_limits<float>::infinity();
	}
	else if (x1 > x0)
	{
		x_inc = 1;
		n += int(floor(x1)) - x;
		error = (floor(x0) + 1 - x0) * dy;
	}
	else
	{
		x_inc = -1;
		n += x - int(floor(x1));
		error = (x0 - floor(x0)) * dy;
	}

	if (dy == 0)
	{
		y_inc = 0;
		error -= std::numeric_limits<float>::infinity();
	}
	else if (y1 > y0)
	{
		y_inc = 1;
		n += int(floor(y1)) - y;
		error -= (floor(y0) + 1 - y0) * dx;
	}
	else
	{
		y_inc = -1;
		n += y - int(floor(y1));
		error -= (y0 - floor(y0)) * dx;
	}

	for (; n > 0; --n)
	{
		if (myTiles.Access(static_cast<unsigned short>(x), static_cast<unsigned short>(y)).CollisionTestRay(rayTrace) == true)
		{
			return true;
		}

		if (error > 0)
		{
			y += y_inc;
			error -= dx;
		}
		else
		{
			x += x_inc;
			error += dy;
		}
	}
	return false;
#pragma endregion
}

void PartionGrid::AssignCirclesToTiles()
{
	for (unsigned short iCircle = 0; iCircle < myCircles.Size(); ++iCircle)
	{
		Circle & tempCircle = myCircles[iCircle];

		CU::Vector2us minPos = CU::Vector2us(static_cast<unsigned short>(tempCircle.GetPosition().x), static_cast<unsigned short>(tempCircle.GetPosition().y));
		minPos.x -= 24;
		minPos.y -= 24;

		CU::Vector2us maxPos = CU::Vector2us(static_cast<unsigned short>(tempCircle.GetPosition().x), static_cast<unsigned short>(tempCircle.GetPosition().y));
		maxPos.x += 24;
		maxPos.y += 24;

		minPos /= 40;
		maxPos /= 40;

		CU::Vector2us testVector = maxPos - minPos;
		int apa = 10;

		for (unsigned short iY = minPos.y; iY <= maxPos.y; ++iY)
		{
			for (unsigned short iX = minPos.x; iX <= maxPos.x; ++iX)
			{
				myTiles.Access(iX, iY).SetObjectOnTop(&myCircles[iCircle]);
			}
		}
	}
}
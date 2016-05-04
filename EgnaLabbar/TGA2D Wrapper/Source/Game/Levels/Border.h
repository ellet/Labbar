#pragma once
#include <tga2d\engine.h>

class Border
{
public:
	Border();
	Border(Vector2f aNode1, Vector2f aNode2);
	void Render() const;
	void DragNode1(Vector2f aNewPosition);
	void DragNode2(Vector2f aNewPosition);
	void MoveLine(Vector2f aNewPosition);
	void SetColour(Vector4f aColour);
	float GetLength(void);
	const Vector2f &GetNode1() const;
	const Vector2f &GetNode2() const;
	~Border();
private:
	Vector2f myNode1;
	Vector2f myNode2;
	Vector4f myColour;
};


#include "stdafx.h"
// Labb 1.cpp : Defines the entry point for the console application.
//



#include "Vectors\Vector2.h"
#include "Vectors\Vector4.h"
#include "Vectors\Vector3.h"
#include <iostream>

template class Vector2 < float >;
template class Vector4 < float >;
template class Vector3 < float >;

int _tmain(int argc, _TCHAR* argv[])
{
	Vector2<float> myApa;
	Vector2<float> mybutt;
	myApa.x = 0.f;
	myApa.y = 7.f;

	std::cout << myApa.GetNormalized().x << " " << myApa.GetNormalized().y << std::endl;

	system("pause");
	return 0;
}
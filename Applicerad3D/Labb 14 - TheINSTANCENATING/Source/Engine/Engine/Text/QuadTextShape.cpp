#include "stdafx.h"
#include "QuadTextShape.h"
#include "Engine/Text/TextVertex.h"
namespace ENGINE_NAMESPACE
{
	QuadTextShape::QuadTextShape()
	{
		std::array<TextVertex, 4> vertices =
		{
			TextVertex{ Vector4f(0.f, 1.f, 0.5f, 1.f),  Vector4f(0.f, 1.f, 0.f, 0.f) },
			TextVertex{ Vector4f(1.f, 1.f, 0.5f, 1.f),   Vector4f(1.f, 1.f, 0.f, 0.f) },
			TextVertex{ Vector4f(0.f, 0.f, 0.5f, 1.f), Vector4f(0.f, 0.f, 0.f, 0.f) },
			TextVertex{ Vector4f(1.f, 0.f, 0.5f, 1.f),  Vector4f(1.f, 0.f, 0.f, 0.f) }
		};

		std::array<unsigned int, 6> indices =
		{
			1, 0, 2,
			1, 2, 3
		};

		CreateBuffers(&vertices[0], static_cast<int>(vertices.size()), &indices[0], static_cast<int>(indices.size()));
	}


	QuadTextShape::~QuadTextShape()
	{
	}
}
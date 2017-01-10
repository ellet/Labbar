#pragma once
#include "Engine\Model\Model.h"

namespace SB
{
	class Texture;

	class TriangleModel : public Model
	{
	public:
		TriangleModel(std::shared_ptr<Texture> aTexture);
		~TriangleModel();
	};
}

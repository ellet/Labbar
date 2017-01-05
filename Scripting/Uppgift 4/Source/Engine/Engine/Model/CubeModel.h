#pragma once
#include "Engine\Model\Model.h"

namespace SB
{
	class Texture;

	class CubeModel : public Model
	{
	public:
		CubeModel(const std::shared_ptr<Texture> & aTexture);
		~CubeModel();
	};

}

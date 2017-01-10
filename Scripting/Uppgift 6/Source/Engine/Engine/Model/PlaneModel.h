#pragma once
#include "Engine\Model\Model.h"

namespace SB
{
	class Texture;

	class PlaneModel : public Model
	{
	public:
		PlaneModel(const std::shared_ptr<Texture> & aTexture, int aTextureTileU = 1, int aTextureTileV = 1);
		~PlaneModel();
	};

}

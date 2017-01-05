#pragma once
#include "Engine\Model\Model.h"

namespace SB
{
	class Texture;

	class Skybox : public Model
	{
	public:
		Skybox(const std::shared_ptr<Texture> & aTexture);
		~Skybox();
		bool MakeReady(bool aLoadAsynchronously) override;

	private:
		Surface mySurface;
	};
}

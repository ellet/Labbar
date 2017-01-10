#include "stdafx.h"
#include "Engine\Model\PlaneModel.h"
#include "Engine\Model\Mesh.h"
#include <Engine/Vertex/Vertex.h>

namespace SB
{

	PlaneModel::PlaneModel(const std::shared_ptr<Texture> & aTexture, int aTextureTileU, int aTextureTileV)
	{
		std::array<Vertex, 4> verticies;
		std::array<unsigned int, 6> indicies =
		{
			0, 1, 2,
			1, 3, 2
		};

		for (size_t i=0; i<verticies.size(); i++)
		{
			verticies[i].normal = Vector3f(0.f, 1.f, 0.f);
			verticies[i].tangent = Vector3f(1.f, 0.f, 0.f);
			verticies[i].bitangent = Vector3f(0.f, 0.f, -1.f);
		}

		verticies[0].position = Vector4f(-0.5f, 0.f, 0.5f, 1.f);
		verticies[0].uv = Vector2f(0.f, 0.f);

		verticies[1].position = Vector4f(0.5f, 0.f, 0.5f, 1.f);
		verticies[1].uv = Vector2f(static_cast<float>(aTextureTileU), 0.f);

		verticies[2].position = Vector4f(-0.5f, 0.f, -0.5f, 1.f);
		verticies[2].uv = Vector2f(0.f, static_cast<float>(aTextureTileV));

		verticies[3].position = Vector4f(0.5f, 0.f, -0.5f, 1.f);
		verticies[3].uv = Vector2f(static_cast<float>(aTextureTileU), static_cast<float>(aTextureTileV));

		Surface surface;
		surface.SetSlot(SurfaceTextureIndex::eDiffuse, aTexture);

		AddMesh(std::make_shared<Mesh<Vertex>>(surface, verticies, indicies));
	}

	PlaneModel::~PlaneModel()
	{
	}

}

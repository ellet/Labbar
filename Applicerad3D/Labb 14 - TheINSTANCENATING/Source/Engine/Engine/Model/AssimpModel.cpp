#include "stdafx.h"
#include "Engine\Model\AssimpModel.h"
#include <FBXLoader.h>
#include "Engine\Vertex\Vertex.h"
#include "Engine\Texture\Texture.h"

namespace ENGINE_NAMESPACE
{
	AssimpModel::AssimpModel(const std::string & aFilePath)
		: AsynchronousResource(aFilePath)
	{
	}

	void AssimpModel::Reload()
	{
		Reset();

		CFBXLoader loader;
		CLoaderModel * model = loader.LoadModel(GetPath().c_str());

		std::string modelDirectory;
		size_t lastSlash = GetPath().find_last_of("\\/");
		if (lastSlash == std::string::npos)
		{
			modelDirectory = "";
		}
		else
		{
			modelDirectory = GetPath().substr(0, lastSlash + 1);
		}
		if (model == nullptr)
		{
			//return;
			Error("A model could not be loaded. Did you forget to add a mesh (perhaps to a prefab)?");
		}

		for (size_t i = 0; i < model->myMeshes.size(); i++)
		{
			CLoaderMesh * mesh = model->myMeshes[i];

			AddMesh(std::make_shared<AssimpMesh>(mesh, modelDirectory));
		}

		const int diffuseSlot = 0;
		const int normalSlot = 5;
		const int roughnessSlot = 1;
		const int ambientOcclusionSlot = 2;
		const int emissiveSlot = 3;
		const int metalnessSlot = 10;

		TryLoadTexture(*model, mySurface, modelDirectory, diffuseSlot, SurfaceTextureIndex::eDiffuse);
		TryLoadTexture(*model, mySurface, modelDirectory, normalSlot, SurfaceTextureIndex::eNormal);
		TryLoadTexture(*model, mySurface, modelDirectory, roughnessSlot, SurfaceTextureIndex::eRoughness);
		TryLoadTexture(*model, mySurface, modelDirectory, ambientOcclusionSlot, SurfaceTextureIndex::eAmbientOcclusion);
		TryLoadTexture(*model, mySurface, modelDirectory, emissiveSlot, SurfaceTextureIndex::eEmissive);
		TryLoadTexture(*model, mySurface, modelDirectory, metalnessSlot, SurfaceTextureIndex::eMetalness);

		for (size_t j = 0; j < GetMeshes().size(); j++)
		{
			GetMeshes()[j]->SetSurface(mySurface);
		}

		// Load all of our textures on this thread
		for (int i = 0; i<static_cast<int>(SurfaceTextureIndex::eCount); i++)
		{
			mySurface.GetSlot(static_cast<SurfaceTextureIndex>(i))->Prepare(false);
		}

		delete model;
	}

	void AssimpModel::Render(const std::shared_ptr<Effect>& aEffect, const Matrix44f& aMatrix, const Matrix44f & aLastFrameMatrix, const Vector4f& aColor) const
	{
		if (const_cast<AssimpModel*>(this)->MakeReady(true))
		{
			Model::Render(aEffect, aMatrix, aLastFrameMatrix, aColor);
		}
	}

	void AssimpModel::InstantRender(const std::shared_ptr<Effect>& aEffect, const Matrix44f & aWorldMatrix, const Matrix44f & aLastFrameMatrix, const Vector4f & aColor) const
	{
		if (const_cast<AssimpModel*>(this)->MakeReady(true))
		{
			Model::InstantRender(aEffect, aWorldMatrix, aLastFrameMatrix, aColor);
		}
	}

	ResourceStatus AssimpModel::GetLoadStatus() const
	{
		return GetStatus();
	}

	bool AssimpModel::MakeReady(bool aLoadAsynchronously)
	{
		return Prepare(aLoadAsynchronously);
	}

	AssimpModel::~AssimpModel()
	{
	}

	void AssimpModel::Load()
	{
		Reload();
	}

	void AssimpModel::TryLoadTexture(const CLoaderModel & model, Surface & surface, const std::string & aModelDirectory, const int aLoadFromSlot, const SurfaceTextureIndex aLoadIntoSlot)
	{
		if (model.myTextures[aLoadFromSlot].length() > 0)
		{
			surface.SetSlot(aLoadIntoSlot, Engine::GetResourceManager().Get<Texture>(aModelDirectory + model.myTextures[aLoadFromSlot]));
		}
	}

	AssimpMesh::AssimpMesh(CLoaderMesh * aMesh, const std::string & aModelDirectory)
		: Mesh(Surface())
	{
		const char * meshVertices = reinterpret_cast<const char*>(aMesh->myVerticies);

		std::vector<Vertex> vertices;
		vertices.resize(aMesh->myVertexCount);
		size_t readOffset = 0;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			if ((aMesh->myShaderType & EModelBluePrint_Position) != 0)
			{
				vertices[i].position = *reinterpret_cast<const Vector4f*>(&meshVertices[readOffset]);
				readOffset += sizeof(Vector4f);
			}
			else
			{
				vertices[i].position = Vector4f(0.f, 0.f, 0.f, 1.f);
			}

			if ((aMesh->myShaderType & EModelBluePrint_Normal) != 0)
			{
				vertices[i].normal = *reinterpret_cast<const Vector4f*>(&meshVertices[readOffset]);
				readOffset += sizeof(Vector4f);
			}
			else
			{
				vertices[i].normal = Vector4f(0.f, 0.f, 0.f, 0.f);
			}

			if ((aMesh->myShaderType & EModelBluePrint_BinormTan) != 0)
			{
				vertices[i].tangent = *reinterpret_cast<const Vector4f*>(&meshVertices[readOffset]);
				readOffset += sizeof(Vector4f);

				vertices[i].bitangent = *reinterpret_cast<const Vector4f*>(&meshVertices[readOffset]);
				readOffset += sizeof(Vector4f);
			}
			else
			{
				vertices[i].tangent = Vector4f(0.f, 0.f, 0.f, 0.f);
				vertices[i].bitangent = Vector4f(0.f, 0.f, 0.f, 0.f);
			}

			if ((aMesh->myShaderType & EModelBluePrint_UV) != 0)
			{
				vertices[i].uv = *reinterpret_cast<const Vector2f*>(&meshVertices[readOffset]);
				readOffset += sizeof(Vector2f);
			}
			else
			{
				vertices[i].uv = Vector2f(0.f, 0.f);
			}

			if ((aMesh->myShaderType & EModelBluePrint_Bones) != 0)
			{
				// vertices[i].position = *reinterpret_cast<const ::Vector4f*>(&meshVertices[i * aMesh->myVertexBufferSize]);
				readOffset += sizeof(Vector4f);
				readOffset += sizeof(Vector4f);
			}
			else
			{
				// vertices[i].position = ::Vector4f(0.f, 0.f, 0.f, 1.f);
			}
		}

		CreateMesh(vertices, aMesh->myIndexes);
	}

}

#pragma once
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"

class CLoaderModel;
class CLoaderMesh;

namespace ENGINE_NAMESPACE
{
	class AssimpMesh;
	struct Vertex;

	class AssimpModel : public Model, public AsynchronousResource
	{
	public:
		AssimpModel(const std::string & aFilePath);
		~AssimpModel();

		void Load() override;
		void Reload() override;

		void Render(const std::shared_ptr<Effect>& aEffect, const Matrix44f& aMatrix, const Matrix44f & aLastFrameMatrix, const Vector4f& aColor) const override;
		void InstantRender(const std::shared_ptr<Effect>& aEffect, const Matrix44f & aWorldMatrix, const Matrix44f & aLastFrameMatrix, const Vector4f & aColor) const override;

		ResourceStatus GetLoadStatus() const override;
		bool MakeReady(bool aLoadAsynchronously) override;



	private:
		void TryLoadTexture(const CLoaderModel & model, Surface & surface, const std::string & aModelDirectory, const int aLoadFromSlot, const SurfaceTextureIndex aLoadIntoSlot);
	private:
		Surface mySurface;
	};

	struct VertexPosColUV;

	class AssimpMesh : public Mesh<Vertex>
	{
	public:
		AssimpMesh(CLoaderMesh * aMesh, const std::string & aModelDirectory);
	};
}

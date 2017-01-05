#pragma once
#include "Engine\Model\Model.h"
#include "Engine\Model\Mesh.h"

class CLoaderModel;
class CLoaderMesh;
class SceneAnimator;


namespace SB
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

		void Render(const Camera & aCamera, const std::shared_ptr<Effect>& aEffect, const Matrix44f& aMatrix, const Matrix44f & aLastFrameMatrix, const Color & aColor, const AnimationPlaybackData * aPlaybackData = nullptr, uint8_t * aCullingCache = nullptr, size_t * aLodCache = nullptr) const override;
		void InstantRender(const Camera & aCamera, const std::shared_ptr<Effect>& aEffect, const Matrix44f & aWorldMatrix, const Matrix44f & aLastFrameMatrix, const Color & aColor, const AnimationPlaybackData * aPlaybackData = nullptr) const override;

		ResourceStatus GetLoadStatus() const override;
		bool MakeReady(bool aLoadAsynchronously) override;

		int GetAnimationIndex(const char * aAnimationName) const;

	private:
		void TryLoadTexture(const CLoaderModel & model, Surface & surface, const std::string & aModelDirectory, const int aLoadFromSlot, const SurfaceTextureIndex aLoadIntoSlot);
		
		Surface mySurface;
		std::unique_ptr<SceneAnimator> mySceneAnimator;
	};

	struct VertexPosColUV;

	class AssimpMesh : public Mesh<Vertex>
	{
	public:
		AssimpMesh(CLoaderMesh * aMesh, const std::string & aModelDirectory);
	};
}

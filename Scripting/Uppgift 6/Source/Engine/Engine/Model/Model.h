#pragma once

namespace SB
{
	class Camera;
	class GenericMesh;
	class Effect;
	struct AnimationPlaybackData;

	class Model
	{
	public:
		Model();
		Model(const std::shared_ptr<GenericMesh> & aMesh);
		virtual ~Model();

		virtual void Render(const Camera & aCamera, const std::shared_ptr<Effect>& aEffect, const Matrix44f& aMatrix, const Matrix44f & aLastFrameMatrix, const Color& aColor, const AnimationPlaybackData * aPlaybackData = nullptr, uint8_t * aCullingCache = nullptr, size_t* aLodCache = nullptr) const;
		virtual void InstantRender(const Camera & aCamera, const std::shared_ptr<Effect>& aEffect, const Matrix44f & aWorldMatrix, const Matrix44f & aOldMatrix, const Color & aColor, const AnimationPlaybackData * aPlaybackData = nullptr) const;

		virtual ResourceStatus GetLoadStatus() const;
		virtual bool MakeReady(bool aLoadAsynchronously);

		const std::vector<std::shared_ptr<GenericMesh>> & GetMeshes() const;

		const BoundingBoxf & GetBoundingBox() const;

		inline bool GetShouldRender() const
		{
			return myShouldRender;
		}
		inline void SetShouldRender(const bool aValue)
		{
			myShouldRender = aValue;
		}

	protected:
		void AddMesh(const std::shared_ptr<GenericMesh> & aMesh);
		void Reset();

		bool myShouldRender;


	private:
		bool TryRenderMeshIndex(const Camera & aCamera, size_t i, const std::shared_ptr<Effect>& aEffect, const Matrix44f & aMatrix, const Matrix44f& aLastFrameMatrix, const Color& aColor, uint8_t * aCullingCache) const;
		std::vector<std::shared_ptr<GenericMesh>> myMeshes;
		BoundingBoxf myBoundingBox;
	};
}

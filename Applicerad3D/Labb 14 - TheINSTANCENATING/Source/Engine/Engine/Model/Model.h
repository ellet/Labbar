#pragma once

namespace ENGINE_NAMESPACE
{

	class GenericMesh;
	class Effect;

	class Model
	{
	public:
		Model();
		Model(const std::shared_ptr<GenericMesh> & aMesh);
		virtual ~Model();

		virtual void Render(const std::shared_ptr<Effect>& aEffect, const Matrix44f& aMatrix, const Matrix44f & aLastFrameMatrix, const Vector4f& aColor) const;
		virtual void InstantRender(const std::shared_ptr<Effect>& aEffect, const Matrix44f & aWorldMatrix, const Matrix44f & aOldMatrix, const Vector4f & aColor) const;

		virtual ResourceStatus GetLoadStatus() const;
		virtual bool MakeReady(bool aLoadAsynchronously);

		const std::vector<std::shared_ptr<GenericMesh>> & GetMeshes() const;

		const BoundingBoxf & GetBoundingBox() const;
	protected:
		void AddMesh(const std::shared_ptr<GenericMesh> & aMesh);
		void Reset();

	private:
		std::vector<std::shared_ptr<GenericMesh>> myMeshes;
		BoundingBoxf myBoundingBox;
	};
}

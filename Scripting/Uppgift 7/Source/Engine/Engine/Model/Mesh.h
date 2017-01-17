#pragma once
#include "Surface.h"

enum D3D_PRIMITIVE_TOPOLOGY;

namespace SB
{
	class GenericVertexBuffer;
	class IndexBuffer;
	struct SimpleVertex;

	class Effect;
	class Texture;

	template<typename TVertex>
	class Mesh;
	
	class GenericMesh
	{
	public:
		virtual ~GenericMesh();

		void SetSurface(const Surface & aSurface);

		void Render(const std::shared_ptr<Effect>& aEffect) const;
		void RenderInstanced(const std::shared_ptr<Effect>& aEffect, int aInstanceCount) const;

		const BoundingBoxf & GetBoundingBox();

		void AssignIdentifier(size_t aIdentifier);
		size_t GetIdentifier() const;

		void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY & aTopology);

		bool HasMinMaxRenderDistance() const;

		float GetMinimumRenderDistance() const;
		float GetMaximumRenderDistance() const;

		void SetMeshName(const std::string & aNameToSet) { myMeshName = aNameToSet; }
		const std::string & GetMeshName() const { return myMeshName; }

		bool Prepare(bool aLoadAsynchronously);
		ResourceStatus GetLoadStatus() const;

	protected:
		void CreateMesh(const void * aVertexData, int aVertexCount, int aVertexSizeInBytes, const unsigned int * aIndexData, int aIndexCount);
		void SetMinMaxRenderDistance(float aMinDistance, float aMaxDistance);
		
	private:
		// Only Mesh<TVertex> may inherit
		template<typename TVertex>
		friend class Mesh;
		GenericMesh(const Surface & aSurface);

		static std::atomic<size_t> ourIdentifierCounter;

		std::unique_ptr<GenericVertexBuffer> myVertexBuffer;
		std::unique_ptr<IndexBuffer> myIndexBuffer;

		int myVertexCount;
		int myIndexCount;
		std::string myMeshName;
		Surface mySurface;
		BoundingBoxf myBoundingBox;
		size_t myIdentifier;
		D3D_PRIMITIVE_TOPOLOGY myTopology;
		float myMinimumRenderDistance;
		float myMaximumRenderDistance;
	};

	inline bool GenericMesh::HasMinMaxRenderDistance() const
	{
		return myMinimumRenderDistance >= 0.f;
	}

	inline float GenericMesh::GetMinimumRenderDistance() const
	{
		return myMinimumRenderDistance;
	}

	inline float GenericMesh::GetMaximumRenderDistance() const
	{
		return myMaximumRenderDistance;
	}

	template<typename TVertex>
	class Mesh : public GenericMesh
	{
	public:
		Mesh(const Surface & aSurface);
		Mesh(const Surface & aSurface, const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount);
		Mesh(const Surface & aSurface, const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData);
		template <size_t TVertexCount, size_t TIndexCount>
		Mesh(const Surface & aSurface, const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData);

		~Mesh();

		void CreateMesh(const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount);
		void CreateMesh(const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData);
		template <size_t TVertexCount, size_t TIndexCount>
		void CreateMesh(const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData);	
	};

	template<typename TVertex>
	Mesh<TVertex>::Mesh(const Surface & aSurface)
		: GenericMesh(aSurface)
	{

	}

	template<typename TVertex>
	Mesh<TVertex>::Mesh(const Surface & aSurface, const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount)
		: GenericMesh(aSurface)
	{
		CreateMesh(aVertexData, aVertexCount, aIndexData, aIndexCount);
	}

	template<typename TVertex>
	Mesh<TVertex>::Mesh(const Surface & aSurface, const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData)
		: Mesh(aSurface, &aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()))
	{
	}

	template<typename TVertex>
	template <size_t TVertexCount, size_t TIndexCount>
	Mesh<TVertex>::Mesh(const Surface & aSurface, const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData)
		: Mesh(aSurface, &aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()))
	{
	}

	template<typename TVertex>
	void Mesh<TVertex>::CreateMesh(const TVertex * aVertexData, int aVertexCount, const unsigned int * aIndexData, int aIndexCount)
	{
		GenericMesh::CreateMesh(aVertexData, aVertexCount, sizeof(TVertex), aIndexData, aIndexCount);

		if (aVertexCount > 0)
		{
			BoundingBoxf bb(aVertexData[0].GetPosition());
			for (int i = 1; i < aVertexCount; i++)
			{
				bb.ExpandToContain(aVertexData[i].GetPosition());
			}
			myBoundingBox = bb;
		}
	}

	template<typename TVertex>
	void Mesh<TVertex>::CreateMesh(const std::vector<TVertex> & aVertexData, const std::vector<unsigned int> & aIndexData)
	{
		CreateMesh(&aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()));
	}

	template<typename TVertex>
	template <size_t TVertexCount, size_t TIndexCount>
	void Mesh<TVertex>::CreateMesh(const std::array<TVertex, TVertexCount> & aVertexData, const std::array<unsigned int, TIndexCount> & aIndexData)
	{
		CreateMesh(&aVertexData[0], static_cast<int>(aVertexData.size()), &aIndexData[0], static_cast<int>(aIndexData.size()));
	}

	template<typename TVertex>
	Mesh<TVertex>::~Mesh()
	{
	}
}

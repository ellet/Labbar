#pragma once

class SpatialObject
{
public:

	struct ConstructData
	{
	public:
		std::string myFilePath;
		float myRotationSpeed;
		float myLocalRotationSpeed;
		float myOrbitSpeed;
		PixelPositionFloat myPosition;
		float mySize;
	};

	SpatialObject();
	~SpatialObject();

	void Init(const ConstructData & aCreationData);
	void Update(const CU::Time & aDeltaTime);

	void Draw(const CU::Matrix33f & aParentMatrix) const;

	void AddChild(SpatialObject & aSpatialObject);
	void SetParentSpace(const CU::Space& aSpace);

	const CU::Vector2f &GetPosition();
	const CU::Matrix33f &GetTransformation();
private:
	HUG::Sprite mySprite;
	float myChildrenRotationSpeed;
	float myLocalRotationSpeed; //Sprite only
	float myOrbitSpeed;
	float myCurrentRotation;

	//CU::Matrix33f myTransformation;
	CU::Space mySpace;
	CU::GrowingArray<SpatialObject*> myChildren;
};
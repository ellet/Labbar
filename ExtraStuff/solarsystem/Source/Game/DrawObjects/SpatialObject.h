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
		PixelPositionFloat myPosition;
		float mySize;
	};

	SpatialObject();
	~SpatialObject();

	void Init(const ConstructData & aCreationData);
	void Update(const CU::Time & aDeltaTime);

	void Draw(const CU::Matrix33f & aParentMatrix) const;

	void AddChild(SpatialObject & aSpatialObject);

	const CU::Vector2f &GetPosition();
	const CU::Matrix33f &GetTransformation();
private:
	HUG::Sprite mySprite;
	float myRotationSpeed;
	float myLocalRotationSpeed;
	float myCurrentRotation;

	CU::Matrix33f myTransformation;
	CU::GrowingArray<SpatialObject*> myChildren;
};
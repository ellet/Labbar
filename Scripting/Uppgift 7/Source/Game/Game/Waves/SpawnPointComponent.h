#pragma once


class SpawnPointComponent : public SB::BaseComponent
{
public:
	SpawnPointComponent();
	~SpawnPointComponent();

	void Initialize() override;
	void Render(const SB::Camera& aCamera) const override;

	void LoadData(SB::DataNode aProperties) override;
	void ToJson(SB::JsonSerializer& aSerializer) const override;

	void OnRemoved() override;

	static inline unsigned short GetTotalSpawnPointCount()
	{
		return ourTotalSpawnPointCount;
	}
	inline unsigned short GetIndex() const
	{
		return myIndex;
	}


private:
	void ActivateSpawnPoint();

	static unsigned short ourTotalSpawnPointCount;
	unsigned short myIndex;
};


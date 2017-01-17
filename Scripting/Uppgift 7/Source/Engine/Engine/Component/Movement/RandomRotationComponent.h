#pragma once

namespace SB
{
	class RandomRotationComponent : public BaseComponent
	{
	public:
		RandomRotationComponent();
		~RandomRotationComponent();

		virtual void Update(const Time & aDeltaTime) override;

		virtual void Initialize() override;

		virtual void ToJson(JsonSerializer &aSerializer) const override;

		virtual void LoadData(DataNode aProperties) override;
		void LoadData(float aRandomValue);

	private:
		Vector3f myRotationDelta;
		float myRandomValue;

		static unsigned short myRandomSeed;
	};

}
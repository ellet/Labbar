#pragma once

namespace SB
{
	class PointLightComponent : public BaseComponent
	{
	public:
		void Initialize() override;
		~PointLightComponent();
		void LoadData(DataNode aProperties) override;
		void ToJson(JsonSerializer &aSerializer) const override;

		Vector3f GetPosition() const;
		float GetRadius() const;
		Vector3f GetColor() const;
		
	private:
		float myRadius;
		Vector3f myColor;
	};
}

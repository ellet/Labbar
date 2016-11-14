#pragma once

namespace ENGINE_NAMESPACE
{
	class PointLightComponent : public BaseComponent
	{
	public:
		void Initialize() override;
		~PointLightComponent();
		void LoadData(DataNode aProperties) override;
		void ToJson() const override;

		Vector3f GetPosition() const;
		float GetRadius() const;
		Vector3f GetColor() const;
		
	private:
		float myRadius;
		Vector3f myColor;
	};
}

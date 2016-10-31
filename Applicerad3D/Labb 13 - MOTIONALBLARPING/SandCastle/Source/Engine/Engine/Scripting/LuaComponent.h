#pragma once
#include "Engine\Component\BaseComponent.h"
namespace ENGINE_NAMESPACE
{
	class Script;

	class LuaComponent : public BaseComponent
	{
	public:
		LuaComponent();
		~LuaComponent();

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render() const override;

		virtual void Initialize() override;

		void SetScript(const std::shared_ptr<Script> & aScript);
		void LoadData(DataNode aProperties) override;


		void ReceiveLuaEvent(const char * aEvent);

	private:
		std::shared_ptr<Script> myScript;
	};
}

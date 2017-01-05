#pragma once
#include "Engine\Component\BaseComponent.h"

#include "Script.h"
namespace SB
{
	class LuaSubscription;
	class Script;

	class LuaComponent : public BaseComponent
	{
	public:
		LuaComponent();
		~LuaComponent();

		virtual void Update(const Time & aDeltaTime) override;
		virtual void Render(const Camera & aCamera) const override;

		virtual void Initialize() override;

		void SetScript(const std::shared_ptr<Script> & aScript);
		void LoadData(DataNode aProperties) override;
		void ToJson(JsonSerializer &aSerializer) const;

		void TestReceiveLuaEvent(const char * aEvent) 
		{ 
			myScript->ExecuteFunction(aEvent); 
		}

		template <typename ... TArgs>
		void ReceiveLuaEvent(const char * aEvent, TArgs &&... aArgs);

	private:
		std::string myScriptPath;
		std::shared_ptr<Script> myScript;

		std::shared_ptr<LuaSubscription> mySubscription;
	};



	template <typename ... TArgs>
	void LuaComponent::ReceiveLuaEvent(const char * aFunction, TArgs &&...aParams)
	{
		myScript->ExecuteFunction(aFunction, aParams...);
	}

}

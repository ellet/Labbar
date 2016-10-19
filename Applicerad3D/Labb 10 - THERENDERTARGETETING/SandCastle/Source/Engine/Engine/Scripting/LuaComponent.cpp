#include "stdafx.h"
#include "LuaComponent.h"
#include "Engine/Scripting/Script.h"
#include "ScriptFile.h"

namespace ENGINE_NAMESPACE
{
	LuaComponent::LuaComponent()
	{
	}


	LuaComponent::~LuaComponent()
	{
	}

	void LuaComponent::Update(const Time & aDeltaTime)
	{
		myScript->LinkGameObject(GetGameObject());

		myScript->PushFloat(aDeltaTime.InSeconds());
		myScript->ExecuteFunction("Update");
	}

	void LuaComponent::Render() const
	{
		myScript->ExecuteFunction("Render");
	}

	void LuaComponent::Initialize()
	{
	}

	void LuaComponent::SetScript(const std::shared_ptr<Script> & aScript)
	{
		myScript = aScript;
	}

	void LuaComponent::LoadData(DataNode aProperties)
	{
		SetScript(Engine::GetResourceManager().Get<ScriptFile>(aProperties["scriptPath"].GetString())->Execute());
	}

	void LuaComponent::ReceiveLuaEvent(const char * aEvent)
	{
		myScript->ExecuteFunction(aEvent);

	}
}

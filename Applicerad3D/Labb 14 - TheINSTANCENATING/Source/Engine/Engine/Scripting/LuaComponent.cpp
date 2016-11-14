#include "stdafx.h"
#include "LuaComponent.h"
#include "Engine/Scripting/Script.h"
#include "ScriptFile.h"

namespace ENGINE_NAMESPACE
{
	LuaComponent::LuaComponent()
	{
		myScriptPath = "";
	}


	LuaComponent::~LuaComponent()
	{
	}

	void LuaComponent::Update(const Time & aDeltaTime)
	{
		myScript->ExecuteFunction("Update", aDeltaTime.InSeconds());
	}

	void LuaComponent::Render() const
	{
		myScript->ExecuteFunction("Render");
	}

	void LuaComponent::Initialize()
	{
		myScript->LinkGameObject(GetGameObject());
		myScript->ExecuteFunction("Initialize");
	}

	void LuaComponent::SetScript(const std::shared_ptr<Script> & aScript)
	{
		myScript = aScript;
	}

	void LuaComponent::LoadData(DataNode aProperties)
	{
		myScriptPath = aProperties["scriptPath"].GetString();
		SetScript(Engine::GetResourceManager().Get<ScriptFile>(myScriptPath)->Execute());
	}

	void LuaComponent::ToJson() const
	{
		SB::JsonSerializer& serializer = SB::Engine::GetJsonSerializer();
		serializer.WriteObject("properties");

		serializer.WriteNode("scriptPath", myScriptPath);

		serializer.StepOut();
		serializer.WriteNode("type", "LuaComponent");
	}

}

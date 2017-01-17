#include "stdafx.h"
#include "LuaComponent.h"
#include "Engine/Scripting/Script.h"
#include "ScriptFile.h"

namespace SB
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

	void LuaComponent::Render(const Camera & aCamera) const
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

	void LuaComponent::ToJson(JsonSerializer &aSerializer) const
	{
		SB::JsonSerializer& serializer = aSerializer;
		serializer.WriteObject("properties");

		serializer.WriteNode("scriptPath", myScriptPath);

		serializer.StepOut();
		serializer.WriteNode("type", "LuaComponent");
	}

}

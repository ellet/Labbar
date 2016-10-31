#include "stdafx.h"
#include "ShaderFile.h"
#include "Shader.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"

namespace ENGINE_NAMESPACE
{
	ShaderFile::ShaderFile(const std::string& aPath)
		: Resource(aPath)
	{
	}

	void ShaderFile::Reload()
	{
		for (auto && it : myLoadedShaders)
		{
			std::shared_ptr<Shader> shader = it.second;

			if (shader != nullptr)
			{
				shader->Reload();
			}
		}
	}

	std::shared_ptr<VertexShader> ShaderFile::GetVertexShader(const std::string& aEntryPoint)
	{
		std::shared_ptr<VertexShader> shader;
		std::shared_ptr<Shader> alreadyLoadedShader = GetLoadedShader(aEntryPoint);
		if (alreadyLoadedShader != nullptr)
		{
			shader = std::dynamic_pointer_cast<VertexShader>(alreadyLoadedShader);
			if (shader == nullptr)
			{
				Error("This shader is already loaded but is of another type!");
			}
		}
		else
		{
			shader = std::make_shared<VertexShader>(GetPath(), aEntryPoint.c_str());
			myLoadedShaders.emplace(aEntryPoint, shader);
		}
		return shader;
	}
	
	std::shared_ptr<PixelShader> ShaderFile::GetPixelShader(const std::string& aEntryPoint)
	{
		std::shared_ptr<PixelShader> shader;
		std::shared_ptr<Shader> alreadyLoadedShader = GetLoadedShader(aEntryPoint);
		if (alreadyLoadedShader != nullptr)
		{
			shader = std::dynamic_pointer_cast<PixelShader>(alreadyLoadedShader);
			if (shader == nullptr)
			{
				Error("This shader is already loaded but is of another type!");
			}
		}
		else
		{
			shader = std::make_shared<PixelShader>(GetPath(), aEntryPoint.c_str());
			myLoadedShaders.emplace(aEntryPoint, shader);
		}
		return shader;
	}

	std::shared_ptr<GeometryShader> ShaderFile::GetGeometryShader(const std::string& aEntryPoint)
	{
		std::shared_ptr<GeometryShader> shader;
		std::shared_ptr<Shader> alreadyLoadedShader = GetLoadedShader(aEntryPoint);
		if (alreadyLoadedShader != nullptr)
		{
			shader = std::dynamic_pointer_cast<GeometryShader>(alreadyLoadedShader);
			if (shader == nullptr)
			{
				Error("This shader is already loaded but is of another type!");
			}
		}
		else
		{
			shader = std::make_shared<GeometryShader>(GetPath(), aEntryPoint.c_str());
			myLoadedShaders.emplace(aEntryPoint, shader);
		}
		return shader;
	}

	std::shared_ptr<Shader> ShaderFile::GetLoadedShader(const std::string& aEntryPoint)
	{
		auto && it = myLoadedShaders.find(aEntryPoint);

		if (it == myLoadedShaders.end())
		{
			return nullptr;
		}

		std::shared_ptr<Shader> shader = it->second;
		
		if (shader == nullptr)
		{
			myLoadedShaders.erase(it);
			return nullptr;
		}

		return shader;
	}
}

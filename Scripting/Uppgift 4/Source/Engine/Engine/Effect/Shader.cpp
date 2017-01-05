#include "stdafx.h"
#include "Engine\Effect\Shader.h"
#include <d3d11.h>
#include <d3dcompiler.h>

namespace SB
{
	Shader::Shader(const std::string& aFilePath) : AsynchronousResource(aFilePath)
	{

	}

	ID3D10Blob * Shader::CreateShader(const std::string & aFileName, const char * aEntryPoint, const char * aCompileProfile, const bool aDoNotAbort)
	{
		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		flags |= D3DCOMPILE_DEBUG;
		flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		LPCSTR profile = aCompileProfile;
		const D3D_SHADER_MACRO defines[] =
		{
			NULL, NULL
		};

		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* shaderBlob = nullptr;

		HRESULT hr = D3DCompileFromFile(std::wstring(aFileName.begin(), aFileName.end()).c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			aEntryPoint, profile,
			flags, 0, &shaderBlob, &errorBlob);

		if (FAILED(hr) == true)
		{
			if (errorBlob)
			{
				std::cout << static_cast<char*>(errorBlob->GetBufferPointer()) << std::endl;
				errorBlob->Release();
				errorBlob = nullptr;
			}
			else if (hr == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND))
			{
				Engine::GetLogger().LogError("Could not load shader {0}, could not find file:\n{1}", aEntryPoint, aFileName);
			}

			if (shaderBlob)
			{
				shaderBlob->Release();
				shaderBlob = nullptr;
			}

			if (aDoNotAbort == false)
			{
				abort();
			}
		}

		return shaderBlob;
	}

	void Shader::Bind() const
	{
	}

	void Shader::Load()
	{
		Reload();
	}

	Shader::~Shader()
	{
	}
}

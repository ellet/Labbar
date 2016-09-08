#pragma once
#include <fstream>
#include "HUGFramework/HUGDXFramework.h"
#include <d3dcompiler.h>
#include <vector>

//TODO:: CreateEffect
//TODO:: CreateLayout

//TODO:: RELEASA SHIT EFTER

namespace HUGEffectHelper
{
	static bool File_exist(const wchar_t * afilename)
	{
		std::ifstream infile(afilename);

		bool isGood = infile.good();
		infile.close();
		return isGood;
	}

	static bool CompileShader(const wchar_t * aShader, const char* aMainFunction, const char * aTarget, ID3D10Blob*& aCodeBlob, std::string & aOutError)
	{
		if (File_exist(aShader) == false)
		{
			aOutError = "Shader not found!";
			return false;
		}

		HRESULT tempResult;
		ID3D10Blob * tempErrorMessage = nullptr;

		UINT tempFlags = 0;
#if defined(DEBUG) || defined( _DEBUG)
		tempFlags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PREFER_FLOW_CONTROL;
#endif

		tempResult = D3DCompileFromFile(aShader, 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, aMainFunction, aTarget, tempFlags, 0, &aCodeBlob, &tempErrorMessage);
		if (FAILED(tempResult))
		{
			aOutError = "Failed to compile Shader";
			OutputDebugString(aOutError.c_str());
		}

		LPVOID tempVoidError = NULL;
		if (tempErrorMessage != nullptr)
		{
			tempVoidError = tempErrorMessage->GetBufferPointer();
			const char* tempConvertBlobMessageToString = static_cast<const char*>(tempVoidError);

			aOutError = tempConvertBlobMessageToString;

			OutputDebugString(aOutError.c_str());

			return false;
		}

		return true;
	}


	//QUE^^ GrowingArray?
	static void CreateLayout(std::vector<D3D11_INPUT_ELEMENT_DESC> & anArray, LPCSTR aName, int aSemanticIndex, DXGI_FORMAT aFormat, int aInputSlot, D3D11_INPUT_CLASSIFICATION aClassification, int aInstancestep)
	{
		D3D11_INPUT_ELEMENT_DESC tempPolygonLayout;
		tempPolygonLayout.SemanticName = aName;
		tempPolygonLayout.SemanticIndex = aSemanticIndex;
		tempPolygonLayout.Format = aFormat;
		tempPolygonLayout.InputSlot = aInputSlot;
		tempPolygonLayout.AlignedByteOffset = anArray.size() > 0 ? D3D11_APPEND_ALIGNED_ELEMENT : 0;
		tempPolygonLayout.InputSlotClass = aClassification;
		tempPolygonLayout.InstanceDataStepRate = aInstancestep;
		anArray.push_back(tempPolygonLayout);
	}
}
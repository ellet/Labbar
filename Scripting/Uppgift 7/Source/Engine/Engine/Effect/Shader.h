#pragma once

struct ID3D10Blob;

namespace SB
{
	class Shader : public AsynchronousResource
	{
	public:
		virtual ~Shader();

		virtual void Bind() const;
		void Load()override;
	protected:
		Shader(const std::string & aFilePath);

		ID3D10Blob * CreateShader(const std::string & aFileName, const char * aEntryPoint, const char * aCompileProfile, const bool aDoNotAbort = false);
	};
}

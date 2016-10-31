#pragma once

struct ID3D10Blob;

namespace ENGINE_NAMESPACE
{
	class Shader
	{
	public:
		virtual ~Shader();

		virtual void Bind() const;
		const std::string & GetPath() const;
		virtual void Reload();

	protected:
		Shader(const std::string & aFilePath);

		ID3D10Blob * CreateShader(const std::string & aFileName, const char * aEntryPoint, const char * aCompileProfile);

	private:
		std::string myPath;
	};
}

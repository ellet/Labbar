#pragma once

struct ID3D11InputLayout;

namespace ENGINE_NAMESPACE
{
	class VertexShader;
	class PixelShader;
	class GeometryShader;
	class InputLayout;

	class Effect
	{
	public:
		Effect();
		~Effect();

		void AttachVertexShader(const std::string & aFileName, const char * aEntryPoint);
		void AttachPixelShader(const std::string & aFileName, const char * aEntryPoint);
		void AttachGeometryShader(const std::string & aFileName, const char * aEntryPoint);

		void Link(const InputLayout & aLayout);

		void Bind() const;

	private:
		std::shared_ptr<VertexShader> myVertexShader;
		std::shared_ptr<PixelShader> myPixelShader;
		std::shared_ptr<GeometryShader> myGeometryShader;

		bool myIsLinked;
		ID3D11InputLayout * myLayout;
	};
}

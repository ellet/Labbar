#pragma once

namespace ENGINE_NAMESPACE
{
	class CommandLineParameters
	{
	public:
		static void CreateInstance();
		static CommandLineParameters & GetInstance();
		static void DestroyInstance();

		void Parse(int argc, char * argv[]);

		bool CheckParameterForValue(const std::string & aParameter, const std::string & aValue) const;
		const std::unordered_set<std::string> & GetValuesForParameter(const std::string & aParameter);
		const std::string & GetFirstValue(const std::string & aParameter, const std::string& aDefaultValue);

	private:
		CommandLineParameters();
		~CommandLineParameters();

		static CommandLineParameters * ourInstance;

		std::unordered_map<std::string, std::unordered_set<std::string>> myParameters;
	};
}

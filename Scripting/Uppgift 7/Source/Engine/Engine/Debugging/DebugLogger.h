#pragma once

namespace SB
{
	enum class ConsoleForegroundColor
	{
		eBlack = 0,
		eBlue = 1,
		eGreen = 2,
		eCyan = 3,
		eRed = 4,
		eMagenta = 5,
		eBrown = 6,
		eWhite = 7,
		eGray = 8,
		eIntenseBlue = 9,
		eIntenseGreen = 10,
		eIntenseCyan = 11,
		eIntenseRed = 12,
		eIntenseMagenta = 13,
		eYellow = 14,
		eIntenseWhite = 15
	};

	enum class ConsoleBackgroundColor
	{
		eBlack = 0,
		eBlue = 1,
		eGreen = 2,
		eCyan = 3,
		eRed = 4,
		eMagenta = 5,
		eBrown = 6,
		eWhite = 7
	};

	class DebugLogger : public IFormattable
	{
	public:
		DebugLogger();
		~DebugLogger();

		template<typename ...TArgs>
		void LogInfo(const std::string & aMessage, const TArgs & ...args);

		template<typename ...TArgs>
		void LogWarning(const std::string & aMessage, const TArgs & ...args);

		template<typename ...TArgs>
		void LogError(const std::string & aMessage, const TArgs & ...args);

		template<typename ...TArgs>
		void LogResource(const std::string & aMessage, const TArgs & ...args);

		void Print(const std::string &aOutput, const std::string & aMessage);

		std::string ToString() const override;
		std::string ToString(const std::string & aFormat) const override;

		void ActivateFilterLog(const std::string & aFilter);
		void DeactivateFilterLog(const std::string & aFilter);

		void SetOutputColor(const std::string & aChannel, ConsoleForegroundColor aForegroundColor = ConsoleForegroundColor::eWhite, ConsoleBackgroundColor aBackgroundColor = ConsoleBackgroundColor::eBlack);

	private:
		std::string Format(const std::string &aOutput, const std::string & aMessage);
		int defaultOutputColor;

		std::unordered_map<std::string, std::ofstream*> myOpenedFiles;
		std::unordered_map<std::string, int> myOutputColors;
		std::ofstream * myUnfilteredLogFile;
		std::string myFileFormat;

		std::string myStartDateTime;
		std::mutex myOutputMutex;
	};

	template<typename ...TArgs>
	void DebugLogger::LogInfo(const std::string & aMessage, const TArgs & ...args)
	{
		Print("info", FormatString(aMessage, args...));
	}

	template<typename ...TArgs>
	void DebugLogger::LogWarning(const std::string & aMessage, const TArgs & ...args)
	{
		Print("warning", FormatString(aMessage, args...));
	}

	template<typename ...TArgs>
	void DebugLogger::LogError(const std::string & aMessage, const TArgs & ...args)
	{
		Print("error", FormatString(aMessage, args...));
	}

	template<typename ...TArgs>
	void DebugLogger::LogResource(const std::string & aMessage, const TArgs & ...args)
	{
		Print("resource", FormatString(aMessage, args...));
	}
}

#pragma once

namespace SB
{
	struct MessageData
	{
		MessageData();
		MessageData(const MessageData & aCopy);
		void operator=(const MessageData & aCopy);
		~MessageData();

		char data[256];
		void(*copyConstructor)(void * aNewMemory, const void * aOldMemory);
		void(*destructer)(void * aMemory);
		uint16_t identifier;
	};

	inline MessageData::MessageData()
		: copyConstructor(nullptr), destructer(nullptr), identifier(0)
	{
	}

	inline MessageData::MessageData(const MessageData& aCopy)
		: MessageData()
	{
		*this = aCopy;
	}

	inline void MessageData::operator=(const MessageData& aCopy)
	{
		if (destructer != nullptr)
		{
			destructer(data);
		}

		aCopy.copyConstructor(data, aCopy.data);

		copyConstructor = aCopy.copyConstructor;
		destructer = aCopy.destructer;
		identifier = aCopy.identifier;
	}

	inline MessageData::~MessageData()
	{
		if (destructer != nullptr)
		{
			destructer(data);
		}
	}
}

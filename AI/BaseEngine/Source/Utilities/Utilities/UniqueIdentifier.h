#pragma once

namespace SB
{
	template <typename TIDType>
	class UniqueIdentifier
	{
	public:

		static std::atomic_uint16_t nextTypeIndex;

		template<typename T>
		static unsigned short GetID()
		{
			static unsigned short id = nextTypeIndex++;

			return id;
		}
	};

	template <typename TIDType>
	std::atomic_uint16_t UniqueIdentifier<TIDType>::nextTypeIndex = 0;
}

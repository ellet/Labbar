#pragma once

namespace ENGINE_NAMESPACE
{

	template <typename TIDType>
	class UniqeIdentifier
	{
	public:

		static unsigned short nextTypeIndex;

		template<typename T>
		static unsigned short GetID()
		{
			static unsigned short id = nextTypeIndex++;

			return id;
		}
	};

	template <typename TIDType>
	unsigned short UniqeIdentifier<TIDType>::nextTypeIndex = 0;

}
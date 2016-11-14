#pragma once

namespace ENGINE_NAMESPACE
{

	template <typename TMessageType>
	class MessageBlocker
	{
		public:
		void Block()
		{
			myBlocker = std::make_shared<Subscription<TMessageType>>(
				[this](const TMessageType& aMessage)
			{
			}
			, 100000, ReceiveResult::eStop
			);
		}

		void Unblock()
		{
			myBlocker = nullptr;
		}
		
	private:
		std::shared_ptr<Subscription<TMessageType>> myBlocker;
	};
}
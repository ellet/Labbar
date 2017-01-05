#pragma once

namespace SB
{
	struct ChangeCursorMessage;
	struct ShowCursorMessage;
	struct ConfineMouseMessage;

	enum class eCursorState
	{
		eNormal,
		eHover,
		eChangeBack
	};


	class Cursor : public Subscriber<ChangeCursorMessage>, public Subscriber<ShowCursorMessage>, public Subscriber<ConfineMouseMessage>
	{
	public:
		Cursor();
		~Cursor();

		HCURSOR GetCurrentCursor();

		virtual ReceiveResult Receive(const ChangeCursorMessage & aMessage) override;
		virtual ReceiveResult Receive(const ShowCursorMessage & aMessage) override;
		virtual ReceiveResult Receive(const ConfineMouseMessage & aMessage) override;

		void ShouldBeHidden(bool aStatement);
		bool IsHidden() const;

		void SetConfinedState(const bool aConfinedFlag);
		bool IsConfined() const;
		

	private:
		void LoadCursors();

		GrowingArray<eCursorState> myStates;

		HCURSOR myNormalCursor;
		HCURSOR myHoverCursor;
		bool myIsHidden;
		bool myIsConfined;
	};

}
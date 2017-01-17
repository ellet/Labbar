#pragma once



class DialogChain;
namespace SB
{


	class Objective : public SB::IFormattable
	{
	public:
		Objective();
		Objective(SB::DataNode aData, const std::function<void()>& aOnCompleteFunction);
		~Objective();

		void Update(const SB::Time & aDeltaTime);
		void Render(const Camera & aCamera) const;

		void SetCounter(unsigned short aValue);
		void IncrementCounter(unsigned short aDecrementValue);
		void DecrementCounter(unsigned short aDecrementValue);

		void Deactivate();
		void Activate();
		const std::string &GetIdentity()const;
		const std::string &GetDescription()const;

		unsigned short GetCounter()const;
		unsigned short GetTarget()const;

		virtual std::string ToString() const override;
		virtual std::string ToString(const std::string &aFormat) const override;

		inline bool GetIsCompleted() const
		{
			return myIsCompleted;
		}
		inline bool TargetReached() const
		{
			return myCounter == myCounterTarget;
		}

		inline bool GetIsActive() const
		{
			return myIsActive;
		}

	private:
		void OnTargetReached();

		std::string myIdentity;
		std::string myDescription;

		std::function<void()> myOnCompleteFunction;

		unsigned short myCounterTarget;
		unsigned short myCounter;

		bool myIsActive;
		bool myIsCompleted;
	};

};
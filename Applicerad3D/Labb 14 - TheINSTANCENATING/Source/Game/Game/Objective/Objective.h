#pragma once


class DialogChain;

class Objective : public SB::IFormattable
{
public:
	Objective();
	Objective(SB::DataNode aData, const std::function<void()>& aOnCompleteFunction = nullptr);
	~Objective();

	void Update(const SB::Time & aDeltaTime);
	void Render() const;

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

	bool TargetReached() const;
	bool GetIsDialogDone() const;

	inline bool GetIsActive() const
	{
		return myIsActive;
	}

private:
	std::string myIdentity;
	std::string myDescription;

	std::unique_ptr<DialogChain> myDialogChain;

	unsigned short myCounterTarget;
	unsigned short myCounter;

	bool myIsActive;
};


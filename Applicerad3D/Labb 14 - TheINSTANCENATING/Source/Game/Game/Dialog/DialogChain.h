#pragma once

class DialogNode;

class DialogChain
{
public:
	DialogChain();
	DialogChain(SB::DataNode aData, const std::function<void()>& aOnCompleteFunction = nullptr);
	~DialogChain();

	void Start();
	void Reset();

	void Update(const SB::Time& aDeltaTime);
	void Render() const;

	void LoadData(SB::DataNode aData);
	void AddDialogNode(std::shared_ptr<DialogNode> aNode);

	inline bool GetIsDone() const
	{
		return myIsDone;
	}

private:
	bool AdvanceToNextDialogNode();

	SB::GrowingArray<std::shared_ptr<DialogNode>> myDialogNodes;
	std::function<void()> myOnCompleteFunction;
	int myVoiceID;
	unsigned short myCurrentPlayingNode;
	bool myIsDone;
};


#pragma once
class DialogNode
{
public:
	DialogNode();
	DialogNode(SB::DataNode aData);
	~DialogNode();

	void Update(const SB::Time& aDeltaTime);
	void Render() const;

	void Start();
	void Reset();

	void LoadData(SB::DataNode aData);

	inline bool GetIsDonePlaying() const
	{
		return myCurrentDuration <= 0.f;
	}

private:
	void DetermineDuration();

	SB::Text mySubtitles;
	std::string myVoiceClip;
	SB::Time myTotalDuration;
	SB::Time myCurrentDuration;
	SB::Time myTrailDelay;
};


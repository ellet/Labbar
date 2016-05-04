#pragma once
class Animation
{
public:

	Animation();
	Animation(const unsigned short aFirstFrame, const unsigned short aFrameCount, const float aDisplayTime);
	~Animation();

	inline unsigned short GetFirstFrame() const;
	inline void SetFirstFrame(const unsigned short anIndex);

	inline unsigned short GetFrameCount() const;
	inline void SetFrameCount(const unsigned short aCount);

	inline float GetDisplayTime() const;
	inline void SetDisplayTime(const float aTime);

private:

	unsigned short myFirstFrame;
	unsigned short myFrameCount;

	float myDisplayTime;

};

inline unsigned short Animation::GetFirstFrame() const
{
	return myFirstFrame;
}
inline void Animation::SetFirstFrame(const unsigned short anIndex)
{
	myFirstFrame = anIndex;
}

inline unsigned short Animation::GetFrameCount() const
{
	return myFrameCount;
}
inline void Animation::SetFrameCount(const unsigned short aCount)
{
	myFrameCount = aCount;
}

inline float Animation::GetDisplayTime() const
{
	return myDisplayTime;
}
inline void Animation::SetDisplayTime(const float aTime)
{
	myDisplayTime = aTime;
}

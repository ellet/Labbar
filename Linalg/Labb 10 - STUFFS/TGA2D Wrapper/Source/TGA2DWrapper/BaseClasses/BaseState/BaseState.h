#pragma once

class BaseState
{
public:

	BaseState();
	virtual ~BaseState();

	virtual void Init();

	inline bool GetActiveUpdate() const;
	inline void SetActiveUpdate(const bool aFlag);

	inline bool GetActiveDraw() const;
	inline void SetActiveDraw(const bool aFlag);

	virtual void Update(const float aDeltaTime);
	virtual void Draw() const;

	virtual void DoOnChangeFrom();
	virtual void DoOnChangeTo();

private:

	bool myActiveFlagUpdate;
	bool myActiveFlagDraw;

};

inline bool BaseState::GetActiveUpdate() const
{
	return myActiveFlagUpdate;
}
inline void BaseState::SetActiveUpdate(const bool aFlag)
{
	myActiveFlagUpdate = aFlag;
}

inline bool BaseState::GetActiveDraw() const
{
	return myActiveFlagDraw;
}
inline void BaseState::SetActiveDraw(const bool aFlag)
{
	myActiveFlagDraw = aFlag;
}

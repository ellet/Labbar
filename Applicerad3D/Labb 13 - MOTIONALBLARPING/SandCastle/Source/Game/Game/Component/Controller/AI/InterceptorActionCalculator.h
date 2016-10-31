#pragma once
enum class ActionScoreResult
{
	eNoAction = 0,
	eAccelerate,
	eTurnAwayFromPlayer,
	eTurnAwayFromPoint,
	eRotateTowardsPlayer,
	eStartToBreak,
	eShootAtPlayer
};
struct ActionScore
{
	ActionScoreResult myResult;
	int myValue;
};
struct InterceptorActionScores
{
	ActionScore myAccelerate;
	ActionScore myStartToBreak;
	ActionScore myTurnAwayFromPlayer;
	ActionScore myRotateTowardsPlayer;
	ActionScore myShootAtPlayer;
	ActionScore myTurnAwayFromPoint;
};

class AIInterceptorComponent;
class InterceptorActionCalculator
{
public:
	InterceptorActionCalculator();
	~InterceptorActionCalculator();
	ActionScoreResult CalculateActionScore(AIInterceptorComponent * aInterceptor);
	void CalculateAccelerationScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores);
	void CalculateTurnAwayFromPoint(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores);
	void CalculateTurnAwayFromPlayerScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores);
	void CalculateRotateTowardsPlayerScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores);
	void CalculateShootAtPlayerScore(AIInterceptorComponent * aInterceptor, InterceptorActionScores & aActionScores);
	ActionScoreResult CalculateResult(InterceptorActionScores & aActionScores);
	void SetObjects(SB::GameObject* aPlayer, SB::GameObject* aInterceptor);
private:
	SB::GameObject* myPlayer;
	SB::GameObject* myInterceptor;
};


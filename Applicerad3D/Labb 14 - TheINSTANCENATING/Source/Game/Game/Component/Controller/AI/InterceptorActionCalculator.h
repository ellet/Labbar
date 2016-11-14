#pragma once
enum class ActionScoreResult
{
	eNoAction = 0,
	eAccelerate,
	eTurnAwayFromPlayer,
	eTurnAwayFromPoint,
	eRotateTowardsPlayer,
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
	void InterceptorActionCalculator::LoadData(SB::DataNode aProperties);
	void SetObjects(SB::GameObject* aPlayer, SB::GameObject* aInterceptor);

	void ToJson()const;
private:
	SB::GameObject* myPlayer;
	SB::GameObject* myInterceptor;
	float myDistanceToPlayerUntilRotate;
	int myRotateTowardsPlayerPoints;
	int myIsRotatingPoints;
	int myShootAtPlayerPoints;
	int myTurnAwayFromClusterPoints;
	int myTurnAwayFromObjectPoints;

	float GetAngleToAvoidObject(AIInterceptorComponent * aInterceptor, const SB::GameObject* aGameObject);
	bool WillHitObject(AIInterceptorComponent * aInterceptor, const SB::GameObject* aGameObject);
};


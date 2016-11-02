#include "ScoreCounter.h"

ScoreCounter::ScoreCounter()
{
}

ScoreCounter::~ScoreCounter()
{

}

void ScoreCounter::Init()
{
	myText = new hgeFont("Data/font1.fnt");
	myScore = 0;
}

void ScoreCounter::Render()
{
	myText->printf(10,10,HGETEXT_LEFT,"Score: %d",myScore);
}

void ScoreCounter::AddScore(int aScore)
{
	myScore += aScore;
}
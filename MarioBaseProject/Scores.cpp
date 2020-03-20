#include "Scores.h"

Scores::Scores()
{
	
}

Scores::~Scores()
{
	
}

int Scores::GetScore(int index)
{
	if (index == 1)
		return tempScore1;
	if (index == 2)
		return tempScore2;
}

void Scores::StoreTemp(int index, int value)
{
	if (index == 1)
		tempScore1 = value;
	if (index == 2)
		tempScore2 = value;
}
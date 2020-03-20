#pragma once
#include <iostream>
using namespace std;

class Scores
{
private:
	int tempScore1,
	    tempScore2;

public:
	Scores();
	~Scores();
	int GetScore(int index);
	void StoreTemp(int index, int value);
};
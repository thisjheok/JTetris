#include "Score.h"

void Score::increaseScore(int increment)
{
	score = getScore() + increment;
}

int Score::getScore() const
{
	return score;
}

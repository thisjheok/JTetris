#pragma once

class Score {
public:
	void increaseScore(int increment);
	int getScore() const;
private:
	int score = 0;
};
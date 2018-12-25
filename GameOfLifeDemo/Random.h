#pragma once
#include <cmath> 

class Random
{
private:

public:
	int seed = 1;

	//! Constructor of random with seed setting.
	Random(int seed);

	//!Seed setting.
	void SetSeed(int seed);
	
	//!return float value from 0.0-1.0
	//possible result : 0.0f, 0.43f, 0.333f, 0.9023f, 1.0f, etc.
	static float random_0_1(void);

	//!return float value in between min, max (including min and max itself)
	//exp : rani(10.0f, 20.0f), possible results :10.4f, 19.334f, 12.047f, etc
	static float randf(float min, float max);

	//!return int value in between min, max (including min and max itself)
	//exp: rani(10, 20), possible results: 11, 12, 16, 20, etc
	static int randi(int min, int max);

};

#include "Random.h"

Random::Random(int seed)
{
	this->seed = seed;
	srand(seed);
}

void Random::SetSeed(int seed)
{
	this->seed = seed;
	srand(seed);
}

float Random::random_0_1(void)
{
	float tempRand = rand() % 2;
	return tempRand;
}

float Random::randf(float min, float max)
{
	float tempRand = ((float)rand() / (float)RAND_MAX) * (max - min) + min;
	return tempRand;
}

int Random::randi(int min, int max)
{
	int tempRand = min + rand() % (max - min + 1);
	return tempRand;
}

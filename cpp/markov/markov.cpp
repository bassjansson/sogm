
#include <iostream>

using namespace std;


static int seed = (int)time(NULL);

void cumulatief(float* kans)
{
	float helper = 0;

	for(int i = 0; kans[i] != -1; i++) helper += kans[i];
	for(int i = 0; kans[i] != -1; i++) kans[i] /= helper;

	helper = 0;

	for(int i = 0; kans[i] != -1; i++) kans[i] = helper = kans[i] + helper;
}

float frand()
{
	srand(seed);
	seed = rand();
	return seed / (float)RAND_MAX;
}

int markov(float* cumulatieve)
{
	float random = frand();

	for(int i = 0; cumulatieve[i] != -1; i++)
		if(random < cumulatieve[i]) return i;

	return -1;
}

int main()
{
	float kans[] = {10, 1, 1, 10, 1, 10, 1, 10, 1, 1, 10, 1, -1};

	cumulatief(kans);

	for(int i = 0; i < 20; i++)
	{
		cout << markov(kans) << endl;
	}
}


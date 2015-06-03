/*Random.cpp
*Implements the Random Number interface
*/

#include "Random.h"
#include "stdlib.h"
#include <Windows.h>
#include <cmath>
/*Prototypes for "private functions"
*Function: initRandomSeed
*Usage: initRandomSeed()
*This seeds the random number generator if it has not been seeded already
*/
void initRandomSeed();


/*Function: randomInteger
*Implementation Notes = how did I solve the problem?
*/
int randomInteger(int a, int b)
{
	initRandomSeed();
	double normal = rand() / (double(RAND_MAX) + 1);
	double scaled = normal * (double(b) - a + 1);
	return int(floor(a + scaled));
}


/*Function: randomReal
*Usage: number = randomReal(low, high);
*Description: returns a psuedo-ranom double value in the range [low, high)
Similar to randomInt - no conversion to int at the end
*/
double randomReal(double a, double b)
{
	initRandomSeed();
	double normal = rand() / (double(RAND_MAX) + 1);
	double scaled = normal * (double(b) - a);
	return (a + scaled);
}

/*Function: randomChance
*Usage: if(randomChance(percent)) ...
*Description: Returns true with probability percent and false with probability 1 - percent
*/
bool randomChance(double percentage)
{
	initRandomSeed();
	return randomReal(0, 1) < percentage;
}


/*Function: initRandomSeed*/
void initRandomSeed()
{
	static bool initialized = false;

	if (!initialized)
	{
		srand(GetTickCount());
		initialized = true;
	}
}
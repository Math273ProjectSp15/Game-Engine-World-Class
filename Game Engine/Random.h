/*Random.h
*Exports functionality for generating random integers and real numbers withing a specified range.
*Exports a function for generating true with some probability.
*/
//Could also use #pragma once here
#ifndef _RANDOM_H
#define _RANDOM_H


/*Function: randomInteger
*Usage: number = randomInteger(low, high);
*Description: Returns a pseudo-random integer between low and high, inclusive.
*/
int randomInteger(int a, int b);

/*Function: randomReal
*Usage: number = randomReal(low, high);
*Description: returns a psuedo-ranom double value in the range [low, high)
*/
double randomReal(double a, double b);

/*Function: randomChance
*Usage: if(randomChance(percent)) ...
*Description: Returns true with probability percent and false with probability 1 - percent
*/
bool randomChance(double percentage);




#endif
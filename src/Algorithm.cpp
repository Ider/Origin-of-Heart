/*
 *  Algorithm.cpp
 *  WindowOfHeart
 *
 *  Created by Ider on 11/8/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include <cstdlib>
#include <ctime>
#include "Algorithm.h"

///////////////////////////////////////////////////////////////
//Initialize random number generator
void Random::Initialize()
{
	srand ( time(NULL) );
}

///////////////////////////////////////////////////////////////
//Return a random float value in range [min, max].
//The larger the precision is, the more random value it could generate.
float Random::Float(float min, float max, unsigned int precision)
{
	if (min > max)
	{
		float temp = min;
		min = max;
		max = temp;
	}
	
	//if only one random value required, return min
	if (precision <= 1) return min;
	
	//Generate random value
	float range = max - min;
	float ratio = float(rand()%(precision))/float(precision-1);
	
	return (range * ratio + min);
}

///////////////////////////////////////////////////////////////
//Return a random float value in range [min, max].
int Random::Int(int min, int max)
{
	if (min > max) min ^= max ^= min^= max;
	
	int range = max - min + 1;
	return (rand()%range + min);
}

#ifdef TEST_IDER_ALGORITHM


#include <iostream>
using namespace std;
int main()
{
	float x = 0.3;
	float y = 0.4;
	
	float z = 0.5;
	
	float array[] = 
	{
		0.3,0.4,0.5
	};
	Norm<float>::Normalize(x, y, z);
	cout << "x: " << x <<", y: " << y;
	
	Norm<float>::Normalize(array,3);
	cout << "[0]: " << array[0]
		<<", [1]: " << array[1] 
		<<", [2]: " << array[2];

	
	return 0;
}

#endif
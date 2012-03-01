
#ifndef ROOT_FINDER
#define ROOT_FINDER
/*
 *  RootFinder.h
 *  OriginOfHeart
 *
 *  Created by Ider on 11/4/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
class Expression 
{
public:
	virtual ~ Expression(){}
	
	virtual float operator()(float x){ return 0.0; }
	virtual float operator()(float x, float y){ return 0.0; }
	virtual float operator()(float x, float y, float z){ return 0.0; }
};

class RootFinderAlgorithm
{
public:
	
	static bool QuadraticFormula(float a, float b, float c, float& r1, float& r2);
	static bool Bisection(Expression& exp, float para1, float para2, float& root);
	
	static void SetApproximate(float min, float max);
private:
	static bool ApproximationCheck(float& value);
	
	static float approximate[2];
};


typedef RootFinderAlgorithm RFA;



#endif
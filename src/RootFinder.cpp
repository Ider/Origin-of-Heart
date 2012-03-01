/*
 *  RootFinder.cpp
 *  OriginOfHeart
 *
 *  Created by Ider on 11/4/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include <cmath>
#include "RootFinder.h"
float RFA::approximate[2] = { 0.00001, -0.000001};


///////////////////////////////////////////////////////////////
//http://en.wikipedia.org/wiki/Quadratic_equation
bool RFA::QuadraticFormula(float a, float b, float c, float& r1, float& r2)
{
	//Quadratic formula
	float delta = b*b - 4*a*c;
	//if delta less than 0, the expression has no root
	if (delta < 0) return false;
	
	float del = pow(delta, 0.5);
	
	r1 = (-b + del)/(2*a);
	r2 = r1 - del/a; // (-b - del)/(2*a);
	
	return true;
}

///////////////////////////////////////////////////////////////
//Check if the value is in (-approximate, approximate)
//Actually we want to check if value is equal to 0.0, but because of
//the accuracy of float number, we should check a rang
bool RFA::Bisection(Expression& exp, float para1, float para2, float& root)
{
	float result1 = exp(para1);
	float result2 = exp(para2);
	//if origin points could be the root, return it
	if (ApproximationCheck(result1))
	{
		root = para1;
		return true;
	}
	if (ApproximationCheck(result2))
	{
		root = para2;
		return true;
	}
 
	if (result1*result2>0)return false;
	
	//begin bisection method
	root = (para1 + para2)/2;
	result2 = exp(root);
	float result3 ;
	while (!ApproximationCheck(result2))
	{
		if (result1*result2>0)
			para1 = root;
		else
			para2 = root;
		result1 = exp(para1);
		root = (para1 + para2)/2;
		result2 = exp(root);
		result3 = exp(para2);
	}
		
	return true;
}

///////////////////////////////////////////////////////////////
//Set the approximate range for root check
void RFA::SetApproximate(float min, float max)
{
	approximate[0] = max > min ? max : min; 
	approximate[1] = max > min ? min : max; 
}


///////////////////////////////////////////////////////////////
//Check if the value is in (-approximate, approximate)
//Actually we want to check if value is equal to 0.0, but because of
//the accuracy of float number, we should check a rang
bool RFA::ApproximationCheck(float& value)
{
	return (value <= approximate[0] && value >= approximate[1]);
}


#ifdef ROOT_FINDER_TEST



#include <iostream>
using namespace std;

class ExpTest : public Expression
{
public:
	virtual float operator()(float x)
	{
		float b2 = pow(9.0/80.0*x*x, 2.0/3.0);
		float _4ac = 9*x*x - 4;
		
		return b2 - _4ac;
	}
};

int  main()
{
	float y1,y2;
	RFA::QuadraticFormula(1,-4, 4, y1,y2);
	cout << y1 <<", " << y2<<endl;
	ExpTest ex;
	RFA::Bisection(ex, 0.0f, 5.0f, y1);
	cout << y1 <<endl;
	return 0;
}





#endif

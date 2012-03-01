/*
 *  Point.cpp
 *  OriginOfHeart
 *
 *  Created by Ider on 11/4/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */

#include "Point.h"

#ifdef TEST_IDER_POINT

#include <iostream>
using namespace std;

typedef Point<float> Pf;

int main()
{
	Pf p1 = Pf(1.0,2.0,3);
	cout<<fixed<<setprecision(7);
	p1 = 2.0f * p1;
	cout << "p1:\t"  << p1 <<endl;
	
	Pf p2 = Pf(2.0, 3.0, 4);
	cout << "p2:\t"  << p2<<endl <<endl;

	cout << "Addition:" << (p2+p1)<<endl;
	cout << "Substraction:" << (p2-p1)<<endl;
	cout << "Negative:" << -p1<<endl;
	cout << "Dot:" << (p2*p1)<<endl;
	cout << "Scale:" << (p1*1.5)<<endl;
	cout << "Equality:"<< (p1 == Pf(2.0,4.0,6.0));

	return 0;
}

#endif


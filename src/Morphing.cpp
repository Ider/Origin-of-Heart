/*
 *  Morphing.cpp
 *  OriginOfHeart
 *
 *  Created by Ider on 11/28/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */

#include "Morphing.h"

#ifdef TEST_MORPHING


#include <iostream>
using namespace std;
int main()
{
	
	Morphing<3> m;
	MorphingTrace<3> mt;
	mt.PushStop(Stop());
	mt.PushStop(Stop());
	mt.PushStop(Stop());
	cout << mt.StopCount()<<endl;
	
	MorphingTrace<3> mt2 = mt;
	
	cout << mt2.StopCount()<<endl;

	MorphingTrace<3> mt3;

	cout << mt3.StopCount()<<endl;

		mt3 = mt;
	cout << mt3.StopCount()<<endl;
	
	m.PushTrace(mt);
	return 0;
}
#endif
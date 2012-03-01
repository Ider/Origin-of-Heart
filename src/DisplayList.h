#ifndef DISPLAY_LIST
#define DISPLAY_LIST

/*
 *  DisplayList.h
 *  WindowOfHeart
 *
 *  Created by Ider on 11/8/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */

#include "TaubinHeart.h"

class DisplayList
{
public:
	void Display() const;
	virtual ~ DisplayList();
protected:
	DisplayList();
	unsigned int listId;
};

class HeartList : public DisplayList
{
public:
	static HeartList* Instance();
	virtual ~ HeartList();
protected:
	HeartList();
	static HeartList* instance;
private:
	void DrawVertics(HeartGenerator::Vector& v0, HeartGenerator::Vector& v1);
	void DrawVertics(Point<float>& p0, Point<float>& p1, Point<float>& p2, Point<float>& p3);
	void DrawVertics(Point<float>& p, Point<float>& n);

};


#endif
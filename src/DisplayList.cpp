/*
 *  DisplayList.cpp
 *  WindowOfHeart
 *
 *  Created by Ider on 11/8/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */

#include "DisplayList.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/********************* Display List *********************/

///////////////////////////////////////////////////////////////
//Generate the display list number
DisplayList::DisplayList()
{
	listId = glGenLists(1); 
}

///////////////////////////////////////////////////////////////
//Distroy the display list
DisplayList::~DisplayList()
{
	/* This line may never be called,
	 * as the construtor is protected, no object could be create 
	 * except inside of derived class; and destructor is virtual,
	 * destrutor of derived class will be called instead to delete object
	 */
	glDeleteLists(listId, 1);
}

///////////////////////////////////////////////////////////////
//Call the display list 
void DisplayList::Display() const
{
	glCallList(listId);
}

/********************* Heart List *********************/
HeartList* HeartList::instance = NULL;

///////////////////////////////////////////////////////////////
//Get the single instance of HeartList
HeartList* HeartList::Instance()
{
	//if instance is not initialized, create one
	if (!instance)
		instance = new HeartList();
	
	return instance;
}

///////////////////////////////////////////////////////////////
//Delete the Displaylist when instance distroyed
HeartList::~ HeartList()
{
	//Set instace to NULL
	instance = NULL;
	glDeleteLists(listId, 1);
}

///////////////////////////////////////////////////////////////
//Create the display list for HeartList
HeartList::HeartList()
{
	//Get Heart Vertics Buffer
	HeartBuffer& hb = HeartHelper::GetHeartBuffer();
	
	size_t layers = hb.BufferSize()-1;
	
	glNewList(listId, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	
	for (size_t i = 0; i < layers; i++)
		DrawVertics(*hb[i], *hb[i+1]);
	
	glEnd();
	
	glEndList();
}

///////////////////////////////////////////////////////////////
//Draw each vertics in the layer and next layer,
//combine them into triangles
void HeartList::DrawVertics(HeartGenerator::Vector& v0, HeartGenerator::Vector& v1)
{
	size_t count = v1.size()-1;
	for (size_t i = 0; i < count; i++)
		DrawVertics(v0[i],v0[i+1],v1[i+1],v1[i]);

}
///////////////////////////////////////////////////////////////
//Draw four vertics, combine them into two triangles
void HeartList::DrawVertics(Point<float>& p0, Point<float>& p1, Point<float>& p2, Point<float>& p3)
{
	Point<float> n0 = HeartHelper::NormalAt(p0);
	Point<float> n1 = HeartHelper::NormalAt(p1);
	Point<float> n2 = HeartHelper::NormalAt(p2);
	Point<float> n3 = HeartHelper::NormalAt(p3);
	
	//triangle one
	DrawVertics(p0,n0);
	DrawVertics(p1,n1);
	DrawVertics(p2,n2);

	//triangle two
	DrawVertics(p2,n2);
	DrawVertics(p3,n3);
	DrawVertics(p0,n0);
}

///////////////////////////////////////////////////////////////
//Draw four vertic with normal vector
void HeartList::DrawVertics(Point<float>& p, Point<float>& n)
{
	glNormal3f(n.X, n.Y, n.Z);
	glVertex3f(p.X, p.Y, p.Z);
}

#ifdef DISPALY_LIST_TEST

int main()
{
	return 0;
}

#endif




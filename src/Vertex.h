#ifndef IDER_VERTEX
#define IDER_VERTEX

/*
 *  Vertex.h
 *  OriginOfHeart
 *
 *  Created by Ider on 11/28/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */

#include "Point.h"


class Vertex
{
public:
	Point<float>& Value(){return value;}
	Point<float>& Normal(){return normal;}
	Point<float>& Color(){return color;}
	//Texture Coordinate
	Point<float>& TexCoord(){return texCoord;}

private:
	Point<float> value;
	Point<float> normal;
	Point<float> color;
	Point<float> texCoord;
};




#endif
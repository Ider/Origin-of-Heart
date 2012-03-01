/*
 *  TaubinHeart.cpp
 *  OriginOfHeart
 *
 *  Created by Ider on 11/4/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include <cmath>
#include <iostream>
#include "TaubinHeart.h"
#include "Algorithm.h"

using namespace std;

/********************* Heart Generator *********************/

///////////////////////////////////////////////////////////////
//start vertics generation
void HeartGenerator::Begin()
{
	if (vertices.size() > 0)
		vertices.clear();
	else
	{
		rootFinder.SetApproximate(0.0, 0.00001);
		vertices.reserve(slices*7);
	}
	
	x = 0.0; xStep = 0;
	y = 0.0; yStep = 0;
	
}

///////////////////////////////////////////////////////////////
//Generate next layer vertics
bool HeartGenerator::NextLayer()
{
	if (yStep > stacks)return false;
	y = Y();

	if(!rootFinder.Bisection(*this, 0.0, 1.5, xMax)) return false;
	//xMax = 1.5;
	float z1,z2;
	Vector v1,v2,v3,v4;
	v1.reserve(slices);
	v2.reserve(slices);
	v3.reserve(slices);
	v4.reserve(slices);
	
	for (xStep = 0; xStep <= slices; xStep++)
	{
		x = xStep / float(slices) * xMax;
		
		if(!z(z1,z2))break;
		v1.push_back(Point<float>( x,y,z1));
		v2.push_back(Point<float>( x,y,z2));
		v3.push_back(Point<float>(-x,y,z2));
		v4.push_back(Point<float>(-x,y,z1));			
	}
	
	vertices.clear();
	vertices.swap(v1);
	vertices.insert(vertices.end(),v2.rbegin()+1, v2.rend());
	vertices.insert(vertices.end(),v3.begin()+1, v3.end());
	vertices.insert(vertices.end(),v4.rbegin()+1, v4.rend());
	
	yStep++;
	return true;
}

float HeartGenerator::operator()(float xValue)
{
	x = xValue;
	return (pow(q(), 2.0f) - 4*p());
}

///////////////////////////////////////////////////////////////
//get p value
float HeartGenerator::p()
{
	return (pow(x, 2.0f)+9.0/4.0*pow(y, 2.0f)-1);
}

///////////////////////////////////////////////////////////////
//get q value
float HeartGenerator::q()
{
	float temp = pow(x, 2.0f)+9.0/80.0*pow(y, 2.0f);
	return pow(temp, 1.0f/3.0f);
}

///////////////////////////////////////////////////////////////
//get z values by Quadratic Formula
bool HeartGenerator::z(float& z1, float& z2)
{
	return rootFinder.QuadraticFormula(1,-q(),p(),z1,z2);
}

float HeartGenerator::Y()
{
	float exponent = 1.4;
	//float exponent = yStep < stacks/3 ?1.0f: 7.0f;
	static float max = pow(yMax, exponent);
	float para = yStep / float(stacks) * max;
	return pow(para, 1.0f/exponent);
}


/********************* Heart Buffer *********************/

HeartBuffer::HeartBuffer(int slices, int stacks, bool instantLoad):hg(slices,stacks)
{
	bufferSize = stacks +1;
	if (instantLoad)LoadBuffer();
}

HeartBuffer::~HeartBuffer()
{
	ClearBuffer();
}

///////////////////////////////////////////////////////////////
//Get the index-th layer of vertics, index begin with 0
HeartGenerator::Vector* HeartBuffer::operator[](unsigned int index)
{
	return index >= buffer.size()? NULL : buffer[index];
}

///////////////////////////////////////////////////////////////
//Using HeartGenerator to generate each layer of the vertics,
//save them in buffer for further use
bool HeartBuffer::LoadBuffer()
{
	//there already has data in buffer, do not load again
	if (buffer.size() > 0)return false;
	if (buffer.capacity() < 7)buffer.reserve(bufferSize);
	
	HeartGenerator::Vector* layer;
	
	hg.Begin();
	while (hg.NextLayer())
	{
		layer = new HeartGenerator::Vector();
		layer->swap(hg.Vertices());
		buffer.push_back(layer);
	}

	return true;
}

///////////////////////////////////////////////////////////////
//Clear the data in the buffer and generate
bool HeartBuffer::ReloadBuffer()
{
	ClearBuffer();
	return LoadBuffer();
}

void HeartBuffer::ClearBuffer()
{
	for (size_t i = 0; i < buffer.size(); i++)
		delete buffer[i];
	buffer.clear();
}

/********************* Heart Buffer Singleton *********************/

HeartBuffer* HeartHelper::hb = NULL;

///////////////////////////////////////////////////////////////
//Get an instance of HeartBuffer, as the program only need the same one.
//This could save the time on generate Vertics of Taubin Heart
HeartBuffer& HeartHelper::GetHeartBuffer()
{
	if (!hb)
		hb = new HeartBuffer(40,40);
	
	return *hb;
}

///////////////////////////////////////////////////////////////
//Return the normal vector at point p
Point<float> HeartHelper::NormalAt(const Point<float>& p)
{
	Point<float> n = p ;
	/* The following normal do not make surface look good
	n.X = NormalX(p);	
	n.Y = NormalY(p);	
	n.Z = NormalZ(p);
	*/
	
	/* The sphere normal looks better*/
	Norm<float>::Normalize(n.X, n.Y, n.Z);
	
	return n;
}
/*
///////////////////////////////////////////////////////////////
//X value of the normal vector at point p
float HeartHelper::NormalX(const Point<float>& p)
{
	float c = NormalCommon(p);
	float temp = 6.0 * p.X * c;
	temp -= 2.0 * p.X * p.Z * p.Z * p.Z;
	return temp;
}

///////////////////////////////////////////////////////////////
//Y value of the normal vector at point p
float HeartHelper::NormalY(const Point<float>& p)
{
	float c = NormalCommon(p);
	float temp = 13.5 * p.Y * c;
	temp -= 0.225 * p.Y * p.Z * p.Z * p.Z;
	return temp;
}

///////////////////////////////////////////////////////////////
//Z value of the normal vector at point p
float HeartHelper::NormalZ(const Point<float>& p)
{
	float c = NormalCommon(p);
	float temp = 6.0 * p.Z * c;
	temp -= 3.0 * p.X * p.X * p.Z * p.Z;
	temp -= 0.3375 * p.Y * p.Y * p.Z * p.Z; 
	return temp;	
}

///////////////////////////////////////////////////////////////
//The common formular that each part of normal vector that contains
float HeartHelper::NormalCommon(const Point<float>& p)
{
	float common = p.X * p.X 
				+ 9.0/4.0 * p.Y * p.Y
				+ p.Z * p.Z - 1;
	
	return common*common;
}
*/
#ifdef TEST_TAUBIN_HEART


int main()
{
	/*
	HeartGenerator hg;
	hg.Begin();
	while (hg.NextLayer())
		cout<< hg.Vertices().size()<<endl;
	
	cout << hg(0.0);
	*/
	HeartBuffer hb(50,30);
	
	cout << hb.BufferSize()<<endl;
	
	for (size_t i; i<hb.BufferSize(); i++)
		cout << hb[i]->size()<<endl;
	
	return 0;
}

#endif


#ifndef TAUBIN_HEART
#define TAUBIN_HEART


/*
 *  TaubinHeart.h
 *  OriginOfHeart
 *
 *  Created by Ider on 11/4/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include <vector>
#include "RootFinder.h"
#include "Point.h"

class HeartGenerator : Expression
{
public:
	typedef std::vector< Point<float> > Vector;
	
	HeartGenerator(int slices = 40, int stacks = 10)
	{
		this->slices = slices;
		this->stacks = stacks;
	}
	virtual ~ HeartGenerator(){}
	
	virtual float operator()(float xValue);
	
	void Begin();
	bool NextLayer();
	Vector& Vertices(){return vertices;}
	
	static Point<float> NormalAt(Point<float> p);
private:
	
	float p();
	float q();
	bool z(float& z1, float& z2);
	float x,y;
	int xStep, yStep;
	float Y();
	Vector vertices;
	
	RootFinderAlgorithm rootFinder;
	
	//static const float xMax = 1.13903;
	float xMax;
	static const float yMax = 0.678138;
	int slices;	
	int stacks;
};

class HeartBuffer
{
public:
	typedef std::vector<HeartGenerator::Vector* > Vector;

	HeartBuffer(int slices = 40, int stacks = 10, bool instantLoad = true);
	~ HeartBuffer();
	
	HeartGenerator::Vector* operator[](unsigned int index);
	size_t BufferSize(){return buffer.size();}
	
	bool LoadBuffer();
	bool ReloadBuffer();
	
private:
	void ClearBuffer();
	HeartGenerator hg;
	Vector buffer;
	int bufferSize;
	
};

class HeartHelper
{
public: 
	static HeartBuffer& GetHeartBuffer();
	
	static Point<float> NormalAt(const Point<float>& p);
private:
	/*
	static float NormalX(const Point<float>& p);
	static float NormalY(const Point<float>& p);
	static float NormalZ(const Point<float>& p);
	static float NormalCommon(const Point<float>& p);*/
	
	static HeartBuffer* hb;
};


#endif
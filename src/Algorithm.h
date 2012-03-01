#ifndef IDER_ALGORITHM
#define IDER_ALGORITHM

/*
 *  Algorithm.h
 *  WindowOfHeart
 *
 *  Created by Ider on 11/8/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include <cmath>

class Random
{
public:
	static void Initialize();
	
	float Float(float min = 0.0, float max = 1.0, unsigned int precision = 32768);
	int Int(int min = 0, int max = 100);
};

template <typename T>
class Norm
{
public:
	static void Normalize(T& x)
	{
		const T nil = T();
		if (x != nil)x = T(1.0);
	}
	
	static void Normalize(T& x, T& y)
	{
		const T nil = T();
		
		T module = pow(x, 2.0) + pow(y, 2.0);
		if (module == nil)return;
		
		module = pow(module, 0.5);
		
		x = x / module;
		y = y /module;
	}
	
	static void Normalize(T& x, T& y, T& z)
	{
		const T nil = T();
		const T normal = T(1.0);
		
		T module = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
		if (module == nil || module == normal)return;
		
		module = pow(module, 0.5);
		
		x = x / module;
		y = y / module;
		z = z / module;
	}
	
	static void Normalize(T& x, T& y, T& z, T& a)
	{
		const T nil = T();
		const T normal = T(1.0);
		
		T module = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0) + pow(a, 2.0);
		if (module == nil || module == normal)return;
		
		module = pow(module, 0.5);
		
		x = x / module;
		y = y / module;
		z = z / module;
		a = a / module;
		
	}
	
	static void Normalize(T* array, unsigned int n)
	{
		const T nil = T();
		const T normal = T(1.0);
		
		T module = nil;
		for (unsigned int i = 0; i < n; i++)
			module += pow(array[i], 2.0);
		
		if (module == nil || module == normal)return;
		
		module = pow(module, 0.5);
		for (unsigned int i = 0; i < n; i++)
			array[i] = array[i] / module;
	
	}
};
 
#endif
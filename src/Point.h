#ifndef IDER_POINT
#define IDER_POINT
/*
 *  Point.h
 *  OriginOfHeart
 *
 *  Created by Ider on 11/4/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include <iostream>
#include <iomanip>

///////////////////////////////////////////////////////////////
//Point template class
template<typename T>
struct Point
{
	///////////////////////////////////////////////////////////////
	//Default construtor
	Point()
	{
		X = T();
		Y = T();
		Z = T();
	}
	///////////////////////////////////////////////////////////////
	//Promotion construtor
	Point(T x,
		  T y,
		  T z,
		  T a = T())
	{
		X = x;
		Y = y;
		Z = z;
		A = a;
	}
	///////////////////////////////////////////////////////////////
	//Copy constructor
	Point(const Point<T>& p)
	{
		X = p.X;
		Y = p.Y;
		Z = p.Z;
		A = p.A;
	}
	///////////////////////////////////////////////////////////////
	//Assignment operator
	Point<T>& operator=(const Point<T>& p)
	{
		if (this == &p)return *this;
		
		X = p.X;
		Y = p.Y;
		Z = p.Z;
		A = p.A;
		return *this;
	}
	
	///////////////////////////////////////////////////////////////
	//Subtraction Assignemt operator
	Point<T>& operator+=(const Point<T>& p)
	{
		X += p.X;
		Y += p.Y;
		Z += p.Z;
		A += p.A;
		
		return *this;
	}
	
	///////////////////////////////////////////////////////////////
	//Addition operator
	Point<T> operator+(const Point<T>& p) const
	{
		Point<T> temp = *this;
		temp+= p;
		return temp;
	}
	
	///////////////////////////////////////////////////////////////
	//Negation operator
	Point<T> operator-() const
	{
		return Point(-X, -Y, -Z, -A);
	}
	
	///////////////////////////////////////////////////////////////
	//Subtraction Assignemt operator
	Point<T>& operator-=(const Point<T>& p)
	{
		if (this == &p)
			*this = Point<T>();
		else
			*this += -p;
		
		return *this;
	}
	
	///////////////////////////////////////////////////////////////
	//Subtraction operator
	Point<T> operator-(const Point<T>& p) const
	{
		if (this == &p)return Point<T>();
		Point<T> temp = *this;
		temp -= p;
		return temp;
	}
	
	///////////////////////////////////////////////////////////////
	//Equality operator
	bool operator==(const Point<T>& p) const
	{
		if (this == &p)return true;
		
		return (X == p.X)
		 && (Y == p.Y)
		 && (Z == p.Z)
		 && (A == p.A);
	}
	
	///////////////////////////////////////////////////////////////
	//Dot multiplication operator
	T operator*(const Point<T>& p) const
	{
		T module = T();
		module = X*p.X + Y*p.Y + Z*p.Z + A*p.A;

		return module;
	}
	
	///////////////////////////////////////////////////////////////
	//Scale multiplication assignment
	Point<T>& operator*=(T scale)
	{
		X *= scale;
		Y *= scale;
		Z *= scale;
		A *= scale;
		
		return *this;
	}
	
	///////////////////////////////////////////////////////////////
	//Scale Multiplication
	Point<T> operator*(T scale)const
	{
		Point<T> temp = *this;
		temp *= scale;
		return temp;
	}
	
	//public data member
	T X;
	T Y;
	T Z;
	T A;
};

///////////////////////////////////////////////////////////////
//Point mutiple by Scale
template<typename T>
Point<T> operator*(T scale, const Point<T> & p)
{
	return p * scale;
}

///////////////////////////////////////////////////////////////
//output stream operation
template<typename T>
std::ostream& operator<<(std::ostream& out, const Point<T> &p)
{
	out << std::setw (10) <<  p.X << ';'
	<< std::setw (10) <<  p.Y << ';'
	<< std::setw (10) <<  p.Z ;
	return out;
}

///////////////////////////////////////////////////////////////
//input stream operation
template<typename T>
std::istream& operator>>(std::ostream& in, const Point<T> &p)
{
	throw "Not implemented";
	return in;
}

#endif
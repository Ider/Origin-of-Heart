#ifndef MORPHING
#define MORPHING
/*
 *  Morphing.h
 *  OriginOfHeart
 *
 *  Created by Ider on 11/28/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */

#include <vector>
#include "Point.h"
#include "IDrawable.h"


template<unsigned int S> class MorphingState;

/********************* Data Types for Morphing *********************/
typedef std::vector< Point<float> > Trace;
typedef Point<float> Stop;

class MorphingDirection
{
public:
	enum Direction
	{
		Forward = 1,
		Backward = -1
	};
};

/********************* Morphing Trace *********************/
//'S' indicate how many stop nodes in the Trace for morphing
template<unsigned int S>
class MorphingTrace
{
public:
	/********************* Construtor *********************/
	MorphingTrace(){ trace.reserve(S); }
	MorphingTrace(const MorphingTrace<S>& mt){ trace = mt.trace; }
	MorphingTrace(const Trace& t){ trace = t; }
	
	/********************* Assignment Operator *********************/
	MorphingTrace<S>& operator=(const MorphingTrace<S>& mt)
	{
		if (this == &mt) return * this;
		trace.clear();
		trace = mt.trace;
		return *this;
	}
	
	///////////////////////////////////////////////////////////////
	//Return number of stops in the trace, i.e. the size of trace vector 
	size_t StopCount() const {return trace.size();}
	
	///////////////////////////////////////////////////////////////
	//return the reference to the index-th stop in the trace.
	//No range checked
	Stop& operator[](unsigned int index){ return trace[index]; }
	
	///////////////////////////////////////////////////////////////
	//return the reference to the index-th stop in the trace.
	//No range checked
	const Stop& operator[](unsigned int index) const { return trace[index]; }

	///////////////////////////////////////////////////////////////
	//Push new stop in the end of the trace. 
	//The number of stops could not exceed S.
	bool PushStop(const Stop& s)
	{
		if (trace.size() >= S)return false;

		trace.push_back(s);
		return true;
	}
	
	///////////////////////////////////////////////////////////////
	//Clear the Trace
	void ClearTrace(){ trace.clear(); }
		
private:
	Trace trace;
};

/********************* Morphing *********************/
template<unsigned int S>
class Morphing : public IDrawable
{
public:
	Morphing(){ InitializeData(); }
	virtual ~ Morphing(){ ClearTraces(); }
	
	///////////////////////////////////////////////////////////////
	//Get pointer that pointer to index-th trace in traces vector,
	//if index out of range, return NULL value.
	MorphingTrace<S>* operator[](unsigned int index)
	{
		return	(index>=traces.size()? NULL: traces[index]);
	}
	
	///////////////////////////////////////////////////////////////
	//Return the size of traces vector
	size_t TraceCount() const { return traces.size(); }
	
	///////////////////////////////////////////////////////////////
	//Push new trace to morphing.
	//The stops number of the trace must be exactly S
	bool PushTrace(MorphingTrace<S>& trace)
	{
		if (trace.StopCount() != S) return false;
		
		MorphingTrace<S>* t = new MorphingTrace<S>(trace);
		traces.push_back(t);
		
		return true;
	}
	
	/*
	///////////////////////////////////////////////////////////////
	//A generic version of method that push new trace to morphing.
	//The stops number of the trace must not be less than S
	template<unsigned int T>
	bool PushTrace(MorphingTrace<T>& t)
	{
		throw "Not implemented"
		if (t.StopCount() < S) return false;
		
		return true;
	}
	*/
	
	
	///////////////////////////////////////////////////////////////
	//Delete all traces in the vector, clear the vector
	void ClearTraces()
	{
		for (size_t i = 0; i < traces.size(); i++)
			delete traces[i];
		traces.clear();
	}
	
		
	/********************* State Actions *********************/
	
	void SetState(MorphingState<S> * morphingState){state = morphingState;}
	
	///////////////////////////////////////////////////////////////
	//Getter/Setter of Morphing Direction
	MorphingDirection::Direction Direction()const { return dir;}
	MorphingDirection::Direction& Direction() { return dir;}
	
	///////////////////////////////////////////////////////////////
	//Getter/Setter of Current Stop
	unsigned int CurrentStop() const {return curStop;}
	//Following method is not value safe for assignment,
	//as it do not change the boundary
	unsigned int& CurrentStop() {return curStop;}
	void CurrentStop(unsigned int value) 
	{
		//Set current stop only if the value is less than the 
		if(value < traces.size())
			curStop = value;
	}
	
	///////////////////////////////////////////////////////////////
	//Getter/Setter of Current Steps
	unsigned int CurrentSteps()const {return curSteps;}
	//Following method is not value safe for assignment,
	//as it do not change the boundary	
	unsigned int& CurrentSteps() {return curSteps;}
	void CurrentSteps(unsigned int value) 
	{
		//Set current stop only if the value is less than the 
		if(value <= maxSteps)
			curSteps = value;
	}
	
	///////////////////////////////////////////////////////////////
	//Getter of maximum Steps
	static unsigned int MaxSteps() {return maxSteps;}
	
	//Implement IDrawable interface
	virtual void Draw()
	{
		if (state)
			state->Draw(*this);
	}
	
	static bool& Animated(){ return animated; }
	
private:
	void InitializeData()
	{
		state = NULL;
		curStop = 0;
		curSteps = 0;
		dir = MorphingDirection::Forward;
	}
	
	std::vector<MorphingTrace<S>*> traces;
	
	MorphingState<S>* state;
	MorphingDirection::Direction dir;
	unsigned int curStop; //The current stop that morphing begin with
	unsigned int curSteps;//The current steps that morphing processed
	
	static const unsigned int maxSteps = 1000;
	static bool animated;
};

template<unsigned int S>
bool Morphing<S>::animated;

/************************************************************************************/
/********************* Base Class for State Pattern of Morphing *********************/


template<unsigned int S>
class MorphingState 
{
public:
	MorphingState(){}
	virtual ~ MorphingState(){}

	virtual void ChangeState(Morphing<S>& morph) = 0;
	virtual void Draw(Morphing<S>& morph) = 0;
private:
	
};





#endif
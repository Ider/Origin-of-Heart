#ifndef MORPHING_STATES
#define MORPHING_STATES
/*
 *  HeartMorphingStates.h
 *  OriginOfHeart
 *
 *  Created by Ider on 12/1/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include "Morphing.h"

#define STATE_NUM 2

///////////////////////////////////////////////////////////////
//
class ProcessingState : public MorphingState<STATE_NUM>
{
public:
	virtual ~ ProcessingState(){}
	virtual void ChangeState(Morphing<STATE_NUM>& morph);	
	virtual void Draw(Morphing<STATE_NUM>& morph);
	
private:
	void DrawMorphing(Morphing<STATE_NUM>& morph);
	void DrawMorphing(Stop& curStop, Stop& nextStop, float& stepRatio);
};

///////////////////////////////////////////////////////////////
//
class StopState : public MorphingState<STATE_NUM>
{
public:
	virtual ~ StopState(){}
	virtual void ChangeState(Morphing<STATE_NUM>& morph);
	virtual void Draw(Morphing<STATE_NUM>& morph);
	
private:
	
};

/********************* State for Each Stops *********************/

///////////////////////////////////////////////////////////////
//
class StopBaseState : public MorphingState<STATE_NUM>
{
public:
	StopBaseState() { wait = 0;}
	virtual ~ StopBaseState(){}
	virtual void ChangeState(Morphing<STATE_NUM>& morph);
	//virtual void Draw(Morphing<STATE_NUM>& morph)=0;
	
protected:
	unsigned int wait;
};


///////////////////////////////////////////////////////////////
//
class HeartState : public StopBaseState
{
public:
	virtual ~ HeartState(){}
	//virtual void ChangeState(Morphing<STATE_NUM>& morph);
	virtual void Draw(Morphing<STATE_NUM>& morph);	
private:
	
};


///////////////////////////////////////////////////////////////
//
class SphereState : public StopBaseState
{
public:
	virtual ~ SphereState(){}
	//virtual void ChangeState(Morphing<STATE_NUM>& morph);
	virtual void Draw(Morphing<STATE_NUM>& morph);
	
private:
};


/********************* State Helper *********************/

class StateHelper
{
public:
	
	enum StateType
	{
		Stopover = STATE_NUM,
		Processing = STATE_NUM + 1,
		
		Heart = 0,
		Sphere = 1
		
	};
	//return a PhotoState
	static MorphingState<STATE_NUM>* GetState(StateType stateType);
	static MorphingState<STATE_NUM>* GetState(unsigned int value);
	static Morphing<STATE_NUM>* GetHeartMorphing();
private:
	/********************* State Instance Pointer *********************/
	static ProcessingState* processing;
	static StopState* stop;
	static SphereState* sphere;
	static HeartState* heart;
	
	/********************* Heart Morphing *********************/
	static void GenerateHeartMorphing();
	static void AddTraces(std::vector< Point<float> > & layer);
	static void AddTrace(Stop heart);
	static Morphing<STATE_NUM>* heartMorphing;
};



#endif





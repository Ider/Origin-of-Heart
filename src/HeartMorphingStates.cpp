/*
 *  HeartMorphingStates.cpp
 *  OriginOfHeart
 *
 *  Created by Ider on 12/1/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */

#include "HeartMorphingStates.h"
#include "DisplayList.h"
#include "Algorithm.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

/********************* Processing State *********************/
void ProcessingState::ChangeState(Morphing<STATE_NUM>& morph)
{
	morph.SetState(StateHelper::GetState(StateHelper::Stopover));
}

void ProcessingState::Draw(Morphing<STATE_NUM>& morph)
{
	if (morph.CurrentSteps() >= morph.MaxSteps())
	{
		ChangeState(morph);
		morph.Draw();
		return;
	}

	DrawMorphing(morph);
	if (morph.Animated())
		morph.CurrentSteps() += 1;
}

void ProcessingState::DrawMorphing(Morphing<STATE_NUM>& morph)
{
	unsigned int curStop = morph.CurrentStop();
	unsigned int nextStop = curStop + morph.Direction();
	float curSteps = morph.CurrentSteps();
	float maxSteps = morph.MaxSteps();
	float ratio = curSteps / maxSteps;
	
	unsigned int count = morph.TraceCount();
	
	glDisable(GL_LIGHTING);
	glColor3f(.7, .0, .0);
	glBegin(GL_POINTS);
	
	for (size_t i = 0; i < count; i++)
	{
		MorphingTrace<STATE_NUM>& trace = *morph[i];
		DrawMorphing(trace[curStop], trace[nextStop], ratio);
	}
	
	glEnd();
}

void ProcessingState::DrawMorphing(Stop& curStop, Stop& nextStop, float& stepRatio)
{
	Stop space = nextStop - curStop;
	Stop s = curStop + space*stepRatio;
	glVertex3f(s.X, s.Y, s.Z);
}

/********************* Stop State *********************/
void StopState::ChangeState(Morphing<STATE_NUM>& morph)
{
	//Move stop to next according to the direction of morphing
	unsigned int curStop = morph.CurrentStop() + morph.Direction();
	morph.CurrentStop(curStop);
	
	//Set state associate with current stop
	curStop = morph.CurrentStop();
	morph.SetState(StateHelper::GetState(curStop));
	
	//Clear Steps
	morph.CurrentSteps(0);
	
	//chage the morphing direction
	if (curStop == 0)
		morph.Direction() = MorphingDirection::Forward;
	if (curStop == (STATE_NUM-1))
		morph.Direction() = MorphingDirection::Backward;
}

void StopState::Draw(Morphing<STATE_NUM>& morph)
{
	ChangeState(morph);
	morph.Draw();
}


/********************* Stop Base State *********************/
void StopBaseState::ChangeState(Morphing<STATE_NUM>& morph)
{
	morph.SetState(StateHelper::GetState(StateHelper::Processing));
}

/********************* Heart State *********************/
void HeartState::Draw(Morphing<STATE_NUM>& morph)
{
	glEnable(GL_LIGHTING);
	
	HeartList& hl = *HeartList::Instance();
	//Positive-y part half heart
	hl.Display();
	
	//Negative-y part half heart
	glPushMatrix();
	glRotatef(180.0, 0.0, 0.0, 1.0);
	hl.Display();
	glPopMatrix();
	
	if (morph.Animated())
		wait++;
	if (wait > 2000)
	{
		ChangeState(morph);
		wait = 0;
	}			   
}

/********************* Sphere State *********************/
void SphereState::Draw(Morphing<STATE_NUM>& morph)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glPushMatrix();
	
	glScalef(1.5, 1.5, 1.5);
	//glutWireSphere(1.0, 40, 40);
	glutSolidSphere(1.0, 40, 40);
	glPopMatrix();
	glDisable(GL_NORMALIZE);
	
	if (morph.Animated())wait++;
	if (wait > 2000)
	{
		ChangeState(morph);
		wait = 0;
	}
}

/********************* State Helper *********************/

ProcessingState* StateHelper::processing = new ProcessingState();
StopState* StateHelper::stop = new StopState();
SphereState* StateHelper::sphere = new SphereState();
HeartState* StateHelper::heart = new HeartState();

Morphing<STATE_NUM>* StateHelper::heartMorphing = NULL;

///////////////////////////////////////////////////////////////
//Return a pointer that point to required MorphingState<STATE_NUM> objct
MorphingState<STATE_NUM>* StateHelper::GetState(StateType stateType)
{
	
	switch (stateType)
	{
		case Processing:
			return processing;
			break;
		case Stopover:
			return stop;
			break;
		case Sphere:
			return sphere;
			break;
		case Heart:
			return heart;
			break;
		default:
			return NULL;
			break;
	}
}

///////////////////////////////////////////////////////////////
//Convert unsigned int to StateType, then call GetState(StateType) 
MorphingState<STATE_NUM>* StateHelper::GetState(unsigned int value)
{
	StateType stateType = StateType(value);
	return StateHelper::GetState(stateType);
}

///////////////////////////////////////////////////////////////
//
Morphing<STATE_NUM>* StateHelper::GetHeartMorphing()
{
	if (!heartMorphing)GenerateHeartMorphing();
	
	return heartMorphing;
}

///////////////////////////////////////////////////////////////
//
void StateHelper::GenerateHeartMorphing()
{
	heartMorphing = new Morphing<STATE_NUM>();
	
	HeartBuffer& hb = HeartHelper::GetHeartBuffer();
	size_t layers = hb.BufferSize();
	for (size_t i = 0; i < layers; i++)
		AddTraces(*hb[i]);
}

///////////////////////////////////////////////////////////////
//
void StateHelper::AddTraces(HeartGenerator::Vector& layer)
{
	size_t count = layer.size();
	for (size_t i = 0; i < count; i++)
	{
		Stop heart = layer[i];
		AddTrace(heart);
		
		if (heart.Y != 0.0f)
		{
			heart.Y = -heart.Y;
			AddTrace(heart);
		}
	}
}

void StateHelper::AddTrace(Stop heart)
{
	MorphingTrace<STATE_NUM> t;
	//Push vertex of Heart to the trace
	t.PushStop(heart);
	Random rnd;
	Stop sphere(rnd.Float(-1), rnd.Float(-1), rnd.Float(-1));

	//Push vertex of Sphere to the trace
	Norm<float>::Normalize(sphere.X, sphere.Y, sphere.Z);
	sphere *= 1.5;
	t.PushStop(sphere);
	
	//Push trace to the morphing
	heartMorphing->PushTrace(t);
}

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
	/*cout << mt.StopCount()<<endl;
	
	MorphingTrace<3> mt2 = mt;
	
	cout << mt2.StopCount()<<endl;
	
	MorphingTrace<3> mt3;
	
	cout << mt3.StopCount()<<endl;
	
	mt3 = mt;
	cout << mt3.StopCount()<<endl;
	HeartState hs;
	m.PushTrace(mt);*/
	cout << m.CurrentStop();

	m.CurrentStop()++;
	cout << m.CurrentStop();
	return 0;
}


#endif

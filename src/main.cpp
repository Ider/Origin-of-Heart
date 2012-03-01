/*
 *  main.cpp
 *  OriginOfHeart
 *
 *  Created by Ider on 11/2/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */


#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;

#include "TaubinHeart.h"
#include "Texture.h"
#include "DisplayList.h"
#include "HeartMorphingStates.h"


#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


#define PI 3.14159

static GLfloat windowSize = 1.8;

GLfloat theta = 0.0;

bool halfHeart = false;
unsigned int timersec = 1;
Morphing<2>* hm ;

GLfloat rotModelView[16];

BMPTexture * baby;
BMPTexture * kids;
BMPTexture * sky;
Texture* texture;


void SetView()
{
	//glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glLoadMatrixf(rotModelView);
	gluLookAt(0.0, .0, 0.0, .0, -5.0, 0.0, 0.0, 0.0, 1.0);
}

void DrawBackground()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	
	glLoadIdentity();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture->Bind();
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	
	glTexCoord2f(0.0, 0.0); glVertex3f(-windowSize, -windowSize, -7.0);
	glTexCoord2f(1.0, 0.0); glVertex3f( windowSize, -windowSize, -7.0);
	glTexCoord2f(1.0, 1.0); glVertex3f( windowSize,  windowSize, -7.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-windowSize,  windowSize, -7.0);

	glEnd();
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void display(void)
{
	
	SetView();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();	
	//glRotatef(hTheta, 0.0, .0, 1.0); 
	//glRotatef(vTheta, 1.0, .0, 0.0); 
	
	float matAmbAndDif1[] = {0.9, 0.0, 0.0, 1.0};
	float matAmbAndDif2[] = {0.0, 0.9, 0.0, 1.0};
	float matSpec[] = {1.0, 1.0, 1.0, 1.0};
	float matShine[] = {50.0};
	
	// Position the box for viewing.
	//gluLookAt(0.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	// Material properties of the box.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	
	//	
	//glPointSize(2.0);
	//glEnable(GL_NORMALIZE);
	
	DrawBackground();
	if(halfHeart)
	{
		glEnable(GL_LIGHTING);
		glColor3f(1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glScalef(1.5, 1.5, 1.5);
		HeartList& hl = *HeartList::Instance();
		hl.Display();
		
		/*glPushMatrix();
		glRotatef(180.0, 0.0, 0.0, 1.0);
		hl.Display();
		glPopMatrix();
	
		glEnable(GL_NORMALIZE);
		 glScalef(1.5, 1.5, 1.5);
		 glutSolidSphere(1.0, 40, 40);*/
	}
	else
	{
		hm->Draw();
	}
	
	
	
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glutReshapeWindow(700, 700);
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//	gluPerspective(60.0, (float)w/(float)h, 1.0, 20.0);
	
	glOrtho(-windowSize,windowSize, -windowSize, windowSize, -8.0, 8.0);
	
	
	//glutPostRedisplay();
}

void timerfunc(int value)
{
	if (Morphing<STATE_NUM>::Animated())
		glutTimerFunc(timersec, timerfunc, value);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 's':
			Morphing<STATE_NUM>::Animated() = !Morphing<STATE_NUM>::Animated();
			if (Morphing<STATE_NUM>::Animated())
				glutTimerFunc(217, timerfunc, 0);
			break;
			
		case 'h':
			halfHeart=!halfHeart;
			glutPostRedisplay();
			break;
			
		case '1':
			texture = baby;
			glutPostRedisplay();
			break;
		case '2':
			texture = kids;
			glutPostRedisplay();
			break;
		case '3':
			texture = sky;
			glutPostRedisplay();
			break;

			
		default:
			break;
	}
}

void specialkey(int key, int x, int y)
{
	switch (key)
	{		
		case GLUT_KEY_LEFT:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glRotatef(-10, 0.0,1.0, 0.0);
			glMultMatrixf(rotModelView);
			
			glGetFloatv(GL_MODELVIEW_MATRIX, rotModelView);			
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glRotatef(10, 0.0,1.0, 0.0);
			glMultMatrixf(rotModelView);
			
			glGetFloatv(GL_MODELVIEW_MATRIX, rotModelView);			
			glutPostRedisplay();
			
			break;
			
		default:
			break;
	}
}

GLfloat backupModelView[16];
int mouseX, mouseY;
void mouse(int button, int state, int x, int y)
{
	mouseX = mouseY = -1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf(rotModelView);
		
		glGetFloatv(GL_MODELVIEW_MATRIX, backupModelView);
		mouseX = x;
		mouseY = y;
	}
	
}

void motion(int x, int y)
{
	if (mouseX < 0)return;
	
	
	GLfloat axisX =  (x - mouseX);
	GLfloat axisY =  -(y - mouseY);
	
	GLfloat angel  = pow( axisX*axisX + axisY*axisY, 0.5f) / 4.0;
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glRotatef(angel, -axisY, axisX, 0.0);
	glMultMatrixf(backupModelView);
	
	glGetFloatv(GL_MODELVIEW_MATRIX, rotModelView);

	glutPostRedisplay();
}

void init()
{
	glClearColor(.3, .3, .3, 0.0);
	
	
	glEnable(GL_DEPTH_TEST); // Enable depth testing.
	
	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);
	
	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos[] = { .0, 4.0, 5.0, 1.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };
	
	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	
	glEnable(GL_LIGHT0); // Enable particular light source.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE); // Enable local viewpoint.
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 

	hm = StateHelper::GetHeartMorphing();
	hm->SetState(StateHelper::GetState(StateHelper::Processing));
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, rotModelView);
	
	glPointSize(2.0);
	
	baby = new BMPTexture("baby.bmp");
	kids = new BMPTexture("kids.bmp");
	sky = new BMPTexture("sky.bmp");
	
	texture = baby;
}


int main (int argc, char * argv[]) {
	
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (100, 100);
	
	glutCreateWindow("Origin of Heart");
	
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	
	glutMainLoop();
	
	/*
	 
	 Bisection bis;
	 cout <<bis.GetRoot(0.0, 1.5);
	 */
    return 0;
}

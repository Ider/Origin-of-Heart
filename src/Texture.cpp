/*
 *  Texture.cpp
 *  Trial
 *
 *  Created by Ider on 11/6/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include <fstream>
#include <iostream>
using namespace std;

#include "Texture.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

///////////////////////////////////////////////////////////////
//Constructor
Texture::Texture()
{
	textureId = 0;
	imageData = NULL;
	ok = false;
	//GenerateTexture();
}

Texture::~Texture()
{
	if(imageData) delete[] imageData;
}

///////////////////////////////////////////////////////////////
//Template method, generate texture from image file
void Texture::GenerateTexture()
{
	if(textureId == 0)
		glGenTextures(1, &textureId);
	RetrieveData();
	LoadTexture();
}

///////////////////////////////////////////////////////////////
//Bind this texture for next texture mapping
void Texture::Bind()
{
	if(!ok)GenerateTexture();
	glBindTexture(GL_TEXTURE_2D, textureId);
}

/********************* BMP Texture *********************/

BMPTexture::BMPTexture(const std::string& file_name) : filename(file_name)
{
	
}

BMPTexture::~BMPTexture()
{
	if(imageData) delete[] imageData;
	if(textureId) glDeleteTextures(1, &textureId);
}


///////////////////////////////////////////////////////////////
// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
void BMPTexture::RetrieveData()
{
	unsigned int size, offset, headerSize;
	
	// Read input file name.
	ifstream infile(filename.c_str(), ios::binary);
	
	if(!(ok = infile.good())) return;
	
	// Get the starting point of the image data.
	infile.seekg(10);
	infile.read((char *) &offset, 4); 
	
	// Get the header size of the bitmap.
	infile.read((char *) &headerSize, 4);
	
	// Get width and height values in the bitmap header.
	infile.seekg(18);
	infile.read( (char *) &sizeX, 4);
	infile.read( (char *) &sizeY, 4);
	
	// Allocate buffer for the image.
	size = sizeX * sizeY * 3;
	
	imageData = new unsigned char[size];
	
	// Read bitmap data.
	infile.seekg(offset);
	infile.read((char *) imageData , size);
	
	// Reverse color from bgr to rgb.
	int temp;
	for (int i = 0; i < size; i += 3)
	{ 
		temp = imageData[i];
		imageData[i] = imageData[i+2];
		imageData[i+2] = temp;
	}
	
}

///////////////////////////////////////////////////////////////
//Set parameters for the texture
void BMPTexture::LoadTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureId); 
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//use GL_LINEAR to optimize the image quality
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizeX, sizeY, 0, 
				 GL_RGB, GL_UNSIGNED_BYTE, imageData);
	
	ok = true;
	
	//delete the read in data
	delete[] imageData;
	imageData = NULL;
}

/********************* Mono Color Texture *********************/

///////////////////////////////////////////////////////////////
//Constructor
MonoColorTexture::	MonoColorTexture(int size_x, int size_y, unsigned char r, unsigned char g, unsigned char b)
{
	sizeX = size_x;
	sizeY = size_y;
	color[0] = r;
	color[1] = g;
	color[2] = b;	
}

MonoColorTexture::~ MonoColorTexture()
{
	if(imageData) delete[] imageData;
	if(textureId) glDeleteTextures(1, &textureId);
}


void MonoColorTexture::ResetMonoColor(unsigned char r, unsigned char g, unsigned char b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	RetrieveData();
	
	glBindTexture(GL_TEXTURE_2D, textureId); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizeX, sizeY, 0, 
				 GL_RGB, GL_UNSIGNED_BYTE, imageData);
	
	delete[] imageData;
	imageData = NULL;
}


///////////////////////////////////////////////////////////////
// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
void MonoColorTexture::RetrieveData()
{
	unsigned int size = sizeX * sizeY * 3;
	imageData = new unsigned char[size];
	
	for (int count = 0; count < size; count += 3)
		for (int index = 0; index < 3; index++)
			imageData[count + index] = color[index];
}

///////////////////////////////////////////////////////////////
//Set parameters for the texture
void MonoColorTexture::LoadTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureId); 
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizeX, sizeY, 0, 
				 GL_RGB, GL_UNSIGNED_BYTE, imageData);
	
	ok = true;
	
	//delete the read in data
	delete[] imageData;
	imageData = NULL;
}


int main2()
{
	//Texture * txt = new BMPTexture("what?");
	return 0;
}
#ifndef TEXTURE
#define TEXTURE
/*
 *  Texture.h
 *  Trial
 *
 *  Created by Ider on 11/6/11.
 *  Copyright 2011 Syracuse University. All rights reserved.
 *
 */
#include <string>
/********************* Struct of Texture *********************/
class Texture
{
public:
	Texture();
	virtual ~ Texture();
	
	void Bind();
	bool OK(){ return ok; }
	void GenerateTexture();
	
protected:
	virtual void RetrieveData() = 0;
	virtual void LoadTexture() = 0;
	
	int sizeX;
	int sizeY;
	unsigned char * imageData;
	bool ok;
	unsigned int textureId;
};

/********************* BMP (24 bits) Texture *********************/
class BMPTexture : public Texture
{
public:
	BMPTexture(const std::string& file_name);
	virtual ~ BMPTexture();
	
protected:
	virtual void RetrieveData();
	virtual void LoadTexture();
	std::string filename;
};

/********************* Procedural Texture *********************/
/********************* Mono Color Texture *********************/
class MonoColorTexture : public Texture
{
public:
	MonoColorTexture(int size_x, int size_y, unsigned char r, unsigned char g, unsigned char b);
	virtual ~ MonoColorTexture();
	void ResetMonoColor(unsigned char r, unsigned char g, unsigned char b);
protected:
	virtual void RetrieveData();
	virtual void LoadTexture();
	
	unsigned char color[3];
};

#endif
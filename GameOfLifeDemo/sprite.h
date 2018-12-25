#ifndef SPRITE_H
#define SPRITE_H

#define TEXTURE_COUNT 5

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "lodepng.h"

//! Blending modes.
enum enumBlend
{
	BLEND_ONE = 0, 
	BLEND_ALPHA, //! Alpha blending mode.
	BLEND_ADDITIVE, //! Additive blending mode.
	BLEND_MULTIPLY //! Multiplication blending mode.
};

class Color
{
public:
	float r;
	float g;
	float b;
	float a;
	
	Color()
	{

	}

	Color(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	static Color white;
	static Color black;  
	static Color red;
	static Color green;
	static Color blue;
	static Color yellow;
};


class Sprite
{
private:
	
	unsigned int m_width; // width of the sprite
	unsigned int m_height; // height of the sprite
	GLuint m_TextureID; // Sprite ID
	
public:
	
	Color color;
	// Constructor of sprite.
	Sprite();
	//! Constructor of sprite with image file path address.
	Sprite(const std::string& life);
	// Destructor of sprite.
	virtual ~Sprite();
	//! Load png.file through file path address.
	void loadPNG(const std::string& life);
	// Draw sprite.
	void draw(float x, float y, float scale, float rotation, Color color, enumBlend blendMode);
	//! Return half of the width.
	int halfWidth(float scale);
	//! Return hald of the height.
	int halfHeight(float scale);
};






#endif // ! SPRITE_H


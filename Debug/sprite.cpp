#define _USE_MATH_DEFINES
#include <cmath> 
#include "sprite.h"

Color Color::white = Color(1.0f, 1.0f, 1.0f, 1.0f);
Color Color::black = Color(0.0f, 0.0f, 0.0f, 1.0f);
Color Color::red = Color(1.0f, 0.0f, 0.0f, 1.0f);
Color Color::green = Color(0.0f, 1.0f, 0.0f, 1.0f);
Color Color::blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
Color Color::yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);

Sprite::Sprite()
{
	m_width = 10;
	m_height = 10;
}

Sprite::Sprite(const std::string& life)
{
	glGenTextures(TEXTURE_COUNT, &m_TextureID);
	loadPNG(life);
}

Sprite::~Sprite()
{
	std::cout << "~Sprite" << std::endl;
}

void Sprite::loadPNG(const std::string& life)
{
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, life);

	m_width = width;
	m_height = height;

	if (error != 0)
	{
		std::cout << "png load error: " << error << ": " << lodepng_error_text(error) << std::endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	/*	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	//std::cout << "Printed" << std::endl;
}

int Sprite::halfWidth(float scale)
{
	return m_width * scale * 0.5f;
}

int Sprite::halfHeight(float scale)
{
	return m_height * scale * 0.5f;
}

void Sprite::draw(float x, float y, float scale, float rotation, Color color, enumBlend blendMode)
{
	float radius = sqrt((m_width*0.5) * (m_width*0.5) + (m_height*0.5)*(m_height*0.5));
	float baseDegree = acos(m_width*0.5 / radius);
	//float baseDegree2 = acos(m_height*0.5 / radius);

	rotation = rotation * M_PI / 180;

	float newDegree = baseDegree + rotation;
	//float newDegree2 =  baseDegree2 + rotation;
	float newDegree3 = baseDegree - rotation;

	float newX = (radius * scale) * cos(newDegree);
	float newY = (radius * scale) * sin(newDegree);

	float newX2 = (radius * scale) * cos(newDegree3);//sin(newDegree2);
	float newY2 = (radius * scale) * sin(newDegree3);// cos(newDegree2);

	//std::cout << baseDegree << std::endl;
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	

	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	switch (blendMode)
	{
	case BLEND_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case BLEND_ADDITIVE:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case BLEND_MULTIPLY:
		glBlendFunc (GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
		break;
	}
	
	glBegin(GL_TRIANGLES);

	glColor4f(color.r, color.g, color.b, color.a);

	glTexCoord2f(0, 1);  glVertex2f(x - newX2, y - newY2);
	glTexCoord2f(1, 0);   glVertex2f(x + newX2, y + newY2);
	glTexCoord2f(0, 0);   glVertex2f(x - newX, y + newY);

	glTexCoord2f(1, 0);   glVertex2f(x + newX2, y + newY2);
	glTexCoord2f(1, 1);   glVertex2f(x + newX, y - newY);
	glTexCoord2f(0, 1);   glVertex2f(x - newX2, y - newY2);


	/*glTexCoord2f(0,  1);  glVertex2f(x - (m_width * scale * 0.5), y - (m_height * scale * 0.5));
	glTexCoord2f(1, 0);   glVertex2f(x + (m_width * scale * 0.5), y + (m_height * scale * 0.5));
	glTexCoord2f(0, 0);   glVertex2f(x - (m_width * scale * 0.5), y + (m_height * scale * 0.5));

	glTexCoord2f(1, 0);   glVertex2f(x + (m_width * scale * 0.5), y + (m_height * scale * 0.5));
	glTexCoord2f(1, 1);   glVertex2f(x + (m_width * scale * 0.5), y - (m_height * scale * 0.5));
	glTexCoord2f(0, 1);   glVertex2f(x - (m_width * scale * 0.5), y - (m_height * scale * 0.5));*/

	glDisable(GL_BLEND);
	glEnd();
}


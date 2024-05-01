#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <cstddef>
#include <string>

#include "Vertex.h"
#include "Texture.h"
#include "ResourceManager.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, std::string texturePath);
	void draw();

private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;

	GLuint m_vboID;

	Texture m_texture;
};

#endif  //SPRITE_H
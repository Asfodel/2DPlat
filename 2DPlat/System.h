#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>

#include "Sprite.h"
#include "Errors.h"
#include "Shader.h"
#include "Texture.h"

enum class GameState
{
	PLAY, QUIT
};

class System
{
public:
	System();
	~System();

	void run();
	
private:
	void initSystem();
	void input();
	void gameLoop();
	void render();
	void initShaders();

	SDL_Window* m_window;
	int m_screenWidth;
	int m_screenHeight;
	GameState m_gameState;
	std::vector<Sprite*> m_sprites;
	Shader m_shader;


	float m_time;
};

#endif  //SYSTEM_H
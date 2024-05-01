#include "System.h"

System::System() :
	m_window(nullptr),
	m_screenWidth(1024),
	m_screenHeight(768),
	m_gameState(GameState::PLAY),
	m_time(0.0f)
{}

System::~System()
{}

void System::run()
{
	initSystem();
	m_sprites.push_back(new Sprite());
	m_sprites.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "Texture/ship.png");
	m_sprites.push_back(new Sprite());
	m_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Texture/ship.png");

	gameLoop();
}

void System::initSystem()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("WinName", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		fatalError("SDL window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (glContext == nullptr)
	{
		fatalError("SDL_GL context could not be created!");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not init glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	initShaders();
}

void System::input()
{
	SDL_Event evnt;
	
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::QUIT;
			break;

		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}

}

void System::gameLoop()
{
	while (m_gameState != GameState::QUIT)
	{
		input();
		m_time += 0.01;
		render();
	}
}

void System::render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader.use();

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = m_shader.getUniformLocation("playerTexture");
	glUniform1i(textureLocation, 0);

	//GLuint timeLocation = m_shader.getUniformLocation("time");
	//glUniform1f(timeLocation, m_time);

	for (int i = 0; i < m_sprites.size(); i++)
	{
		m_sprites[i]->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	m_shader.unuse();

	SDL_GL_SwapWindow(m_window);
}

void System::initShaders()
{
	m_shader.compileShader("Shaders/vertex.txt", "Shaders/fragment.txt");
	m_shader.addAttribute("vertexPosition");
	m_shader.addAttribute("vertexColor");
	m_shader.addAttribute("vertexUV");
	m_shader.linkShaders();
}
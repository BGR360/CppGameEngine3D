#include "SDLWindow.h"

namespace Rendering
{
	SDLWindow::SDLWindow()
		: Window("SDL Window")
	{}

	SDLWindow::SDLWindow(string name, int width, int height)
		: Window(name, width, height)
	{}

	void SDLWindow::open()
	{
		//Initialize SDL (TODO: get rid of SDL for Qt)
		m_sdlWindow = SDL_CreateWindow(
			getName().c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			getWidth(),
			getHeight(),
			0);
	}

	void SDLWindow::close()
	{
		SDL_DestroyWindow(m_sdlWindow);
	}

	SDLWindow::~SDLWindow()
	{
		this->close();
		SDL_Quit();
	}
}
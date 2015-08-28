#ifndef BENGINE_SDL_WINDOW_H
#define BENGINE_SDL_WINDOW_H

#include <Engine.h>

#include <sdl/SDL.h>

#include <rendering/window/Window.h>

namespace Rendering
{
	class ENGINE_DLL_EXPORT_IMPORT SDLWindow : public Window
	{
		SDL_Window* m_sdlWindow;

	public:
		SDLWindow();
		SDLWindow(string name, int width = 800, int height = 600);
		virtual ~SDLWindow();

		void open();
		void close();

	private:
		void init(string name, int width, int height);
	};
}

#endif //BENGINE_SDL_WINDOW_H
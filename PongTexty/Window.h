#pragma once

#include "GE161int.h"
#include <string>

namespace GE161
{
	class Window
	{
		friend class Game;

	public:
		// The constructor creates an object, but doesn't create an
		// SDL_WINDOW or an SDL_RENDERER.
		Window();
		~Window();

		// These methods set the size and title
		void size(int width, int height);
		void title(std::string t);

		//create a function to change the back ground color, call this function
		//to change the private color parameters to be called in the cpp.
		void setBGcolor(int r, int g, int b, int a);

		int clientWidth();
		int clientHeight();

	private:
		// The following methods are called by the Game class
		// initialize() creates an SDL_WINDOW and SDL_RENDERER
		bool initialize();
		void clearBackground();
		void drawToScreen();

		//add rgba to be private variables 
		int BGr, BGg, BGb, BGa;
		int width_;
		int height_;
		std::string title_;

		SDL_Window* sdl_window;
		SDL_Renderer* sdl_renderer;

		bool isInitialized;

		static const int MIN_WINDOW_DIMENSION = 100;
		static const int MAX_WINDOW_DIMENSION = 2000;
		static const int DEFAULT_WINDOW_DIMENSION = 100;

	};

}
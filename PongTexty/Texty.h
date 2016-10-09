// Texty.h

#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"

class Texty
{

public:
	Texty(SDL_Renderer* renderer, std::string fontName, int fontSize = 10, bool visible = true);
	~Texty();

	enum writeOption_t {CONTINUE, NEXT_LINE};

	void write(std::string text, writeOption_t option = Texty::CONTINUE);

	void write(std::string text, int x, int y);


private:
	SDL_Renderer* renderer;
	std::string fontName;
	int myfontSize;
	bool myvisible;
	//writeOption_t myoption;
	int X;
	int Y;
	int originalX;
};

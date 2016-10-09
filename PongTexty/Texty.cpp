// Texty.cpp
//1. I create a void function for shwoing error message.
//2. I create a text render function outside the Texty class to: open the font, render it to a surface, and load that surface.
//   My renderText has error checking in each part above (and I have detail comments before each handling process), and I also
//   called SDL_FreeSurface and TTF_CloseFont in the function.
//3. In my two write functions, in order to avoid TTF_RenderText error: Text has zero width, I create two conditions for each,
//   which handles whether the input text string is empty (I also have detail comments before them)

#include "Texty.h"   // You can add or remove #include files as needed.
#include <iostream>
#include <sstream>
#include "Windows.h"


//A void function for shwoing error message
void PopSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

//I create the text render function outside the Texty class
SDL_Texture* renderText(const std::string &message, const std::string &fontFile,
						SDL_Color color, int fontSize, SDL_Renderer *renderer)
{
	//Open the font, handle error if fontfile cannot open
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr){
		PopSDLError(std::cout, "TTF_OpenFont");
		return nullptr;
	}	
	//Render to a surface as that's what TTF_RenderText returns,
	//handle error if surface object is not created
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		PopSDLError(std::cout, "TTF_RenderText");
		return nullptr;
	}
	//Load that surface into a texture, handle error if texture object is not created
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr){
		PopSDLError(std::cout, "CreateTexture");
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}


void Rendertexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}



void Rendertexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst,
				   SDL_Rect *clip = nullptr)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}


void Rendertexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y,
				   SDL_Rect *clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	Rendertexture(tex, ren, dst, clip);
}



Texty::Texty(SDL_Renderer* renderer, std::string fontName, int fontSize, bool visible): myfontSize(fontSize), myvisible(visible)
{
	Texty::renderer = renderer;
	Texty::fontName = fontName;
}

Texty::~Texty()
{
	//Because I call SDL_FreeSurface and TTF_CloseFont in my renderText function,
	//the renderer is deleted in TextyDemo, and I do not have any pointer to clear
	//so I simply do nothing here.
}

void Texty::write(std::string text, writeOption_t option)
{
	//To avoid TTF_RenderText error: Text has zero width, I create two conditions:
	//if the input text is empty: adding Y value for NEXT_LINE, or do nothing but render for CONTINUE
	//else, we do the same as usual
	if (text != "")
	{
		SDL_Color color = {0, 0, 0, 0};
		SDL_Texture *word = renderText(text, fontName, color, myfontSize, renderer);
		if (option == NEXT_LINE){
			Y += myfontSize;
			Rendertexture(word, renderer, originalX, Y);
		}
		else
			Rendertexture(word, renderer, X, Y);
	}
	else
	{
		if (option == NEXT_LINE)
			Y += myfontSize;
	}
}

void Texty::write(std::string text, int x, int y)
{
	//For Part 1:
	//To avoid TTF_RenderText error: Text has zero width, I again create two conditions:
	//if the input text is empty: set X, Y, and originalX to x, y, x
	//else, we do nothing
	Y = y;
	X = x;
	originalX = x;
	SDL_Color color = {0, 0, 0, 0};
	if (text != "")
	{
		//For Part 2:
		//I make Texty \n aware by employing for-loop and checking whether there is a \n character, if there is:
		//I create two variables called "start" and "counter", which counter counts how many characters has been looped.
		//Whenever I find a new line character, I render the substring of the text from "start" to the index of [start + counter-1].
		//Then I reset "start" to current "i", and reset "counter" to zero.
		//I also create an if statement for multiple \n condition: when current "i" is equal to "start", I basically just add Y coordinates
		//and "start."
		//Finally, outside the for loop, I render the last part of text since last \n character. 
		if (text.find ("\n") != std::string::npos){
			int start = 0;
			int counter = 0;
			for (int i = 0; i < text.length(); i++){
				counter++;
				if (text[i] == '\n'){
					//std::cout << i << " " << start << " " << text[i-1] << " " << text[i+1] << "\n";
					if (i - start == 0){
						Y += myfontSize;
						start++;
					}
					else{
						//std::cout << text.substr(30, 54) << "\n";
						SDL_Texture *word = renderText(text.substr(start, counter-1), fontName, color, myfontSize, renderer);
						Rendertexture(word, renderer, X, Y);
						Y += myfontSize;
						start = i+1;
						counter = 0;
					}
				}
			}
			SDL_Texture *word = renderText(text.substr(start), fontName, color, myfontSize, renderer);
			Rendertexture(word, renderer, X, Y);
		}
		else{
			int w, h;
			SDL_Texture *word = renderText(text, fontName, color, myfontSize, renderer);
			SDL_QueryTexture(word, NULL, NULL, &w, &h);
			Rendertexture(word, renderer, X, Y);
			X += w;
		}
	}
}
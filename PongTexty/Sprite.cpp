#include "Sprite.h"
#include "Game.h"


GE161::Sprite::Sprite(int frameWidth, int frameHeight) :
frameWidth_(frameWidth),
frameHeight_(frameHeight)
{
}


GE161::Sprite::~Sprite()
{
}

int GE161::Sprite::makeFrame(std::string fileName, int x, int y)
{
	// Turn this fileName into an SDL_Texture. We only want to do this once,
	// so we store textures in a map, and reuse if needed.
	SDL_Texture* tex;
	if (storedTextures.count(fileName) == 1)  // already seen?
	{
		tex = storedTextures[fileName];
	}
	else
	{
		tex = IMG_LoadTexture(GE161::Game::theGame->getRenderer(), fileName.c_str());
		if (tex == nullptr)
		{
			fatalSDLError("In Sprite::makeFrame(), IMG_LoadTexture: ", SDL_GetError());
			return -1;
		}
		storedTextures[fileName] = tex;
	}
	frame result = {tex, x, y};
	frames.push_back(result);
	return frames.size() - 1;
}

int GE161::Sprite::addFrameToSequence(std::string sequenceName, int frameIndex)
{
	auto p = sequenceList[sequenceName];
	p.first.push_back(frameIndex);
	p.second = 0;
	sequenceList[sequenceName] = p;
	// Note that this method always (re)sets the pointer into the vector
	// of frameIndexes back to 0.  Shouldn't be a problem, since presumably
	// all calls to addFrameToSequence() occur before the sprite starts being drawn.
	return p.first.size();
}

int GE161::Sprite::getNextFrameIndex(std::string sequenceName)
{
	auto p = sequenceList[sequenceName];
	if (p.first.size() == 0)	// sequenceName was not found, so a pair was created.
	{
		fatalSDLError("In Sprite::getNextFrameIndex(), sequenceName was not found: ", sequenceName);
		return 0;
	}
	// Recall that p is a pair; the first part is a vector of frameIndexes, and
	// the second part is an index into that vector, pointing at the next frame to
	// be displayed.
	int frameIndexToReturn = p.first[p.second];
	p.second++;
	if (p.second >= p.first.size())
		p.second = 0;
	sequenceList[sequenceName] = p;
	return frameIndexToReturn;
}


int GE161::Sprite::get_width(){
	return frameWidth_;
}

int GE161::Sprite::get_height(){
	return frameHeight_;
}
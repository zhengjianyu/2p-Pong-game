#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "GE161int.h"

namespace GE161
{
	class Sprite
	{
		friend class GameObject;

	public:
		Sprite(int frameWidth, int frameHeight);
		~Sprite();

		int makeFrame(std::string fileName, int x, int y);
		int addFrameToSequence(std::string sequenceName, int frameIndex);

		//added function to return its width and height
		int get_width();
		int get_height();

	private:
		int getNextFrameIndex(std::string sequenceName);

		int frameWidth_, frameHeight_;

		struct frame
		{
			SDL_Texture* texture;
			int x;		// x and y indicate the upper left hand corner
			int y;		// of the frame in the SDL_Texture
		};
		std::vector<frame> frames;

		// The sequenceList map is use to map a sequenceName string to both
		// a vector of frameIndexes, and the index of the current frameIndex.
		std::map<std::string, std::pair<std::vector<int>, unsigned int>> sequenceList;
		std::map<std::string, SDL_Texture*> storedTextures;
	};

}


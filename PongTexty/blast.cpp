#include "blast.h"

GE161::blast::blast(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::blast::update(){
	draw("blast");
}

void GE161::blast::setup(std::string basePath){
	frameWidth_ = 96;
	frameHeight_ = 96;
	GE161::Sprite* blastSpriteSheet = new GE161::Sprite(frameWidth_, frameHeight_);
	for (int i = 1; i <= 6; i++)
	{
		//std::cout << GE161::Game::basePath() + "blast" + std::to_string(i) + ".png" << std::endl;
		int blastindex = blastSpriteSheet->makeFrame(basePath + "blast" + std::to_string(i) + ".png", 0, 0);
		//std::cout << blastindex << std::endl;
		blastSpriteSheet->addFrameToSequence("blast", blastindex);
	}
	attachSprite(blastSpriteSheet);
	enable_sprites(false);
}

//int GE161::blast::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::blast::get_frameHeight(){
//	return frameHeight_;
//}
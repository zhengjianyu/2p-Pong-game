#include "smoke.h"

GE161::smoke::smoke(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::smoke::update(){
	draw("smoke");
}

void GE161::smoke::setup(std::string basePath){
	frameWidth_ = 192;
	frameHeight_ = 192;
	GE161::Sprite* smokeSpriteSheet = new GE161::Sprite(frameWidth_, frameHeight_);
	for (int i = 1; i <= 10; i++)
	{
		int smokeindex = smokeSpriteSheet->makeFrame(basePath + "smoke" + std::to_string(i) + ".png", 0, 0);
		smokeSpriteSheet->addFrameToSequence("smoke", smokeindex);
	}
	attachSprite(smokeSpriteSheet);
	enable_sprites(false);
}


//int GE161::smoke::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::smoke::get_frameHeight(){
//	return frameHeight_;
//}
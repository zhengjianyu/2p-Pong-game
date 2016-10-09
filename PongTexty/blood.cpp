#include "blood.h"

GE161::blood::blood(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::blood::update(){
	draw("blood");
}


void GE161::blood::setup(std::string basePath){
	frameWidth_ = 128;
	frameHeight_ = 128;
	GE161::Sprite* bloodSpriteSheet = new GE161::Sprite(frameWidth_, frameHeight_);
	for (int i = 1; i <= 6; i++)
	{
		int bloodindex = bloodSpriteSheet->makeFrame(basePath + "blood" + std::to_string(i) + ".png", 0, 0);
		bloodSpriteSheet->addFrameToSequence("blood", bloodindex);
	}
	attachSprite(bloodSpriteSheet);
	enable_sprites(false);
}

//int GE161::blood::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::blood::get_frameHeight(){
//	return frameHeight_;
//}
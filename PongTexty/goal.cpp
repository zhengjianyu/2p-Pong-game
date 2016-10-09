#include "goal.h"

GE161::goal::goal(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::goal::update(){
	draw("goal");
}

void GE161::goal::setup(std::string basePath){
	frameWidth_ = 192;
	frameHeight_ = 192;
	GE161::Sprite* goalSpriteSheet = new GE161::Sprite(frameWidth_, frameHeight_);
	for (int i = 1; i <= 6; i++)
	{
		int goalindex = goalSpriteSheet->makeFrame(basePath + "goal" + std::to_string(i) + ".png", 0, 0);
		goalSpriteSheet->addFrameToSequence("goal", goalindex);
	}
	attachSprite(goalSpriteSheet);
	enable_sprites(false);
}


//int GE161::goal::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::goal::get_frameHeight(){
//	return frameHeight_;
//}
#include "paddle2.h"

GE161::paddle2::paddle2(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::paddle2::update(){
	draw("paddle");
}

void GE161::paddle2::setup(std::string basePath){
	frameWidth_ = 20;
	frameHeight_ = 60;
	GE161::Sprite* paddleSpriteSheet1 = new GE161::Sprite(frameWidth_, frameHeight_);
	int paddleindex1 = paddleSpriteSheet1->makeFrame(basePath + "paddle_green.png", 0, 0);
	paddleSpriteSheet1->addFrameToSequence("paddle", paddleindex1);
	attachSprite(paddleSpriteSheet1);
	enable_sprites(true);
}


//int GE161::paddle2::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::paddle2::get_frameHeight(){
//	return frameHeight_;
//}
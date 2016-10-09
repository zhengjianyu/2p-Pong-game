#include "paddle1.h"

GE161::paddle1::paddle1(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::paddle1::update(){
	draw("paddle");
}

void GE161::paddle1::setup(std::string basePath){
	frameWidth_ = 20;
	frameHeight_ = 60;
	GE161::Sprite* paddleSpriteSheet1 = new GE161::Sprite(frameWidth_, frameHeight_);
	int paddleindex1 = paddleSpriteSheet1->makeFrame(basePath + "paddle_blue.png", 0, 0);
	paddleSpriteSheet1->addFrameToSequence("paddle", paddleindex1);
	attachSprite(paddleSpriteSheet1);
	enable_sprites(true);
}

//int GE161::paddle1::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::paddle1::get_frameHeight(){
//	return frameHeight_;
//}
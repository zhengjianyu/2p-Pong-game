#include "bolt.h"

GE161::bolt::bolt(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::bolt::update(){
	draw("bolt");
}

void GE161::bolt::setup(std::string basePath){
	frameWidth_ = 128;
	frameHeight_ = 128;
	GE161::Sprite* boltSpriteSheet = new GE161::Sprite(frameWidth_, frameHeight_);
	for (int i = 1; i <= 10; i++)
	{
		int boltindex = boltSpriteSheet->makeFrame(basePath + "bolt" + std::to_string(i) + ".png", 0, 0);
		boltSpriteSheet->addFrameToSequence("bolt", boltindex);
	}
	attachSprite(boltSpriteSheet);
	enable_sprites(false);
}


//int GE161::bolt::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::bolt::get_frameHeight(){
//	return frameHeight_;
//}
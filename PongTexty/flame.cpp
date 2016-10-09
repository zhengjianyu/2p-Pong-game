#include "flame.h"

GE161::flame::flame(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::flame::update(){
	draw("flame");
}


void GE161::flame::setup(std::string basePath){
	frameWidth_ = 96;
	frameHeight_ = 96;
	GE161::Sprite* flameSpriteSheet = new GE161::Sprite(frameWidth_, frameHeight_);
	for (int i = 1; i <= 6; i++)
	{
		int flameindex = flameSpriteSheet->makeFrame(basePath + "flame" + std::to_string(i) + ".png", 0, 0);
		flameSpriteSheet->addFrameToSequence("flame", flameindex);
	}
	attachSprite(flameSpriteSheet);
	enable_sprites(false);
}


//int GE161::flame::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::flame::get_frameHeight(){
//	return frameHeight_;
//}
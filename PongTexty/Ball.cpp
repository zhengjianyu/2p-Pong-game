#include "Ball.h"

GE161::Ball::Ball(int x_, int y_) :GameObject(x_, y_)
{
}

void GE161::Ball::update(){
	draw("Rolling");
}

void GE161::Ball::setup(std::string basePath){
	frameWidth_ = 64;
	frameHeight_ = 64;
	GE161::Sprite* ballSpriteSheet = new GE161::Sprite(frameWidth_, frameHeight_);
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			int f = ballSpriteSheet->makeFrame(
				basePath + "RollingBall.png",
				column*frameWidth_, row*frameHeight_);
			//std::cout << f << std::endl;
			ballSpriteSheet->addFrameToSequence("Rolling", f);
		}
	}
	attachSprite(ballSpriteSheet);
	enable_sprites(true);
}


//int GE161::Ball::get_frameWidth(){
//	return frameWidth_;
//}
//
//
//int GE161::Ball::get_frameHeight(){
//	return frameHeight_;
//}
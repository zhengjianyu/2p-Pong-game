#include "GameObject.h"
#include "Game.h"



GE161::GameObject::GameObject(int startingX, int startingY) :
x_(startingX),
y_(startingY),
sprite_(nullptr),
start_draw_(true)
{
}


GE161::GameObject::~GameObject()
{
}

void GE161::GameObject::setPos(int x, int y)
{
	x_ = x;
	y_ = y;
}

void GE161::GameObject::moveX(int delta)
{
	x_ += delta;
}

void GE161::GameObject::moveY(int delta)
{
	y_ += delta;
}

int GE161::GameObject::getX()
{
	return x_;
}

int GE161::GameObject::getY()
{
	return y_;
}

void GE161::GameObject::attachSprite(GE161::Sprite* sprite)
{
	sprite_ = sprite;	
}
void GE161::GameObject::draw(int frameIndex)
{
	if (start_draw_){
		if (sprite_ == nullptr)
		{
			debugOut("GameObject::draw called, but no Sprite is attached.");
			return;
		}

		SDL_Rect srcrect = {sprite_->frames[frameIndex].x, sprite_->frames[frameIndex].y, sprite_->frameWidth_, sprite_->frameHeight_};
		SDL_Rect destrect = {x_, y_, sprite_->frameWidth_, sprite_->frameHeight_};
		int success = SDL_RenderCopy(GE161::Game::theGame->getRenderer(), sprite_->frames[frameIndex].texture, &srcrect, &destrect);
		if (success != 0)
		{
			fatalSDLError("In GameObject::draw, SDL_RenderCopy: ", SDL_GetError());
		}
	}
}

void GE161::GameObject::draw(std::string sequenceName)
{
	if (start_draw_){
		draw(sprite_->getNextFrameIndex(sequenceName));
	}
}


GE161::Sprite* GE161::GameObject::get_sprite(){
	return sprite_;
}

//changing the privates to enable the sprites
void GE161::GameObject::enable_sprites(bool TF){
	if (TF == true)   //reset its duration
		duration = 0;
	start_draw_ = TF;
}

bool GE161::GameObject::get_draw_state(){
	return start_draw_;
}

void GE161::GameObject::update()
{}

void GE161::GameObject::setup(std::string basePath)
{}

//int GE161::GameObject::get_frameWidth()
//{
//	return 0;
//}
//
//int GE161::GameObject::get_frameHeight()
//{
//	return 0;
//}


bool GE161::GameObject::overlapsWith(GameObject& otherGameObject)
{
	//if the sprites are not drawing on the screen, return false
	if (start_draw_ == false)
		return false;
	//added get_sprite() function in GameObject.h
	GE161::Sprite* targetSprite = otherGameObject.get_sprite();
	//if othergameObject has no sprite, just return false
	if (targetSprite == nullptr)
		return false;
	//added get_width() and get_height() function in Sprite.h
	int targetWidth = targetSprite->get_width();
	int targetHeight = targetSprite->get_height();

	GE161::Sprite* selfSprite = this->get_sprite();
	if (selfSprite == nullptr)
		return false;
	int selfWidth = selfSprite->get_width();
	int selfHeight = selfSprite->get_height();

	int self_TopLeftX = this->getX();
	int self_ToprightX = self_TopLeftX + selfWidth;
	int self_TopLeftY = this->getY();
	int self_BotLeftY = self_TopLeftY + selfHeight;

	int target_TopLeftX = otherGameObject.getX();
	int target_ToprightX = target_TopLeftX + targetWidth;
	int target_TopLeftY = otherGameObject.getY();
	int target_BotLeftY = target_TopLeftY + targetHeight;

	if ((target_TopLeftX < self_TopLeftX && self_TopLeftX < target_ToprightX) && (target_TopLeftY < self_TopLeftY && self_TopLeftY < target_BotLeftY))
		return true;
	if ((target_TopLeftX < self_ToprightX && self_ToprightX < target_ToprightX) && (target_TopLeftY < self_TopLeftY && self_TopLeftY < target_BotLeftY))
		return true;
	if ((target_TopLeftX < self_TopLeftX && self_TopLeftX < target_ToprightX) && (target_TopLeftY < self_BotLeftY && self_BotLeftY < target_BotLeftY))
		return true;
	if ((target_TopLeftX < self_ToprightX && self_ToprightX < target_ToprightX) && (target_TopLeftY < self_BotLeftY && self_BotLeftY < target_BotLeftY))
		return true;
	return false;
}

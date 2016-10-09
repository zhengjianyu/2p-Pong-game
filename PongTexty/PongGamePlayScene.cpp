#include "PongGamePlayScene.h"

#include <stdlib.h>		// srand, rand
#include <time.h>		// time
//#include <string>



//PongGamePlayScene.cpp

PongGamePlayScene::PongGamePlayScene(Pong* pong) :
theGame(pong)
{
}

PongGamePlayScene::~PongGamePlayScene()
{
	delete ball;
	//also delete paddles, which are pointers
	delete paddle1;
	delete paddle2;
}

bool PongGamePlayScene::setup()
{
	//get renderer from window;
	SDL_Renderer* renderer = theGame->getRenderer();
	//initialize text;
	std::string basepath = GE161::Game::basePath();

	text = new Texty(renderer, basepath + "FreeSans.ttf", 32, true);


	// Rolling ball sprite sheet is from http://www.java-gaming.org/index.php?topic=21935.0.
	// It has 32 64x64 frames.
	frameWidth_ = 64;
	frameHeight_ = 64;
	//paddle sprite
	paddleWidth_ = 20;
	paddleHeight_ = 60;
	//blast sprite
	blastWidth_ = 96;
	blastHeight_ = 96;
	//goal blast sprite
	goalWidth_ = 192;
	goalHeight_ = 192;
	//smoke sprite
	smokeWidth_ = 192;
	smokeHeight_ = 192;
	//flame sprite
	flameWidth_ = 96;
	flameHeight_ = 96;
	//lightening bolt sprite
	boltWidth_ = 128;
	boltHeight_ = 128;
	//blood sprite
	bloodWidth_ = 128;
	bloodHeight_ = 128;

	// Start the ball with its upper left in the middle of the window.
	ball = new GE161::Ball(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	Entities.push_back(ball);
	paddle1 = new GE161::paddle1(0, theGame->window()->clientHeight() / 2 - paddleHeight_ / 2);
	Entities.push_back(paddle1);
	paddle2 = new GE161::paddle2(theGame->window()->clientWidth() - paddleWidth_, theGame->window()->clientHeight() / 2 - paddleHeight_ / 2);
	Entities.push_back(paddle2);
	//special effect sprites
	blast = new GE161::blast(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	Entities.push_back(blast);
	goal = new GE161::goal(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	Entities.push_back(goal);
	smoke = new GE161::smoke(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	Entities.push_back(smoke);
	flame = new GE161::flame(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	Entities.push_back(flame);
	bolt = new GE161::bolt(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	Entities.push_back(bolt);
	blood = new GE161::blood(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	Entities.push_back(blood);

	exitRequested = false;

	for (int i = 0; i < Entities.size(); i++){
		Entities[i]->setup(basepath);
	}
	
	Ballmovespeed = 1;
	x_delta = y_delta = 1;
	smoke_x_delta = smoke_y_delta = 1;
	flame_x_delta = flame_y_delta = 1;
	blood_x_delta = blood_y_delta = 1;
	//paddle movement
	paddleSpeed = 20;
	bounceCount_ = 0;
	right_bounced_out_ = 0;

	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);
	//register event listener with type = 0
	GE161::Game::registerAsListener(0, this);

	// seed the random number generator with the current time
	srand(static_cast<unsigned int>(time(NULL)));		

	return true;
}

int PongGamePlayScene::draw()
{
	SDL_Event event1;

	text->write(std::to_string(right_bounced_out_), 245, 30);

	ball->moveX(x_delta);
	ball->moveY(y_delta);
	
	for (int i = 0; i < Entities.size(); i++){
		Entities[i]->update();
	}

	ball->duration++;
	if (blast->get_draw_state() == true){
		blast->duration++;
		if (blast->duration > 6)
			blast->enable_sprites(false);
	}
	if (goal->get_draw_state() == true){
		goal->duration++;
		if (goal->duration > 6)
			goal->enable_sprites(false);
	}

	if (ball->duration > 200 && smoke->get_draw_state() == false){
		smoke->enable_sprites(true);
	}

	if (smoke->get_draw_state() == true){
		smoke->moveX(smoke_x_delta);
		smoke->moveY(smoke_y_delta);
		if (smoke->overlapsWith(*ball))
			GE161::Game::sendEvent("SMOKE");
		if (smoke->getY() < 100)
			smoke_y_delta = rand() % 3 + 1;
		if (smoke->getX() < 100)
			smoke_x_delta = rand() % 3 + 1;
		if (smoke->getX() + smokeWidth_ >= theGame->window()->clientWidth() - 100)
			smoke_x_delta = -(rand() % 3 + 1);
		if (smoke->getY() + smokeHeight_ >= theGame->window()->clientHeight() - 100)
			smoke_y_delta = -(rand() % 3 + 1);
	}

	if (flame->get_draw_state() == true){
		flame->moveX(flame_x_delta);
		flame->moveY(flame_y_delta);
		if (flame->overlapsWith(*ball))
			GE161::Game::sendEvent("FLAME");
		if (flame->getY() < 100)
			flame_y_delta = rand() % 3 + 1;
		if (flame->getX() < 100)
			flame_x_delta = rand() % 3 + 1;
		if (flame->getX() + flameWidth_ >= theGame->window()->clientWidth() - 100)
			flame_x_delta = -(rand() % 3 + 1);
		if (flame->getY() + flameHeight_ >= theGame->window()->clientHeight() - 100)
			flame_y_delta = -(rand() % 3 + 1);
	}
	if (bolt->get_draw_state() == true){
		bolt->moveX(3);
		if (bolt->overlapsWith(*paddle2))
			goal->enable_sprites(false);
		else if (bolt->getX() >= theGame->window()->clientWidth()){
			bolt->enable_sprites(false);
			right_bounced_out_++;
		}
	}
	if (blood->get_draw_state() == true){
		blood->moveX(blood_x_delta);
		blood->moveY(blood_y_delta);
		if (blood->overlapsWith(*ball))
			GE161::Game::sendEvent("BLOOD");
		if (blood->getY() < 100)
			blood_y_delta = rand() % 3 + 1;
		if (blood->getX() < 100)
			blood_x_delta = rand() % 3 + 1;
		if (blood->getX() + bloodWidth_ >= theGame->window()->clientWidth() - 100)
			blood_x_delta = -(rand() % 3 + 1);
		if (blood->getY() + bloodHeight_ >= theGame->window()->clientHeight() - 100)
			blood_y_delta = -(rand() % 3 + 1);
	}


	// If the ball has hit an edge, bounce randomly.
	if (ball->overlapsWith(*paddle1))
	{
		x_delta = (rand() % 3 + 1)*Ballmovespeed;
		GE161::Game::sendEvent("COLLIDE");
		bounceCount_++;
	}
	if (ball->overlapsWith(*paddle2))
	{
		x_delta = -(rand() % 3 + 1)*Ballmovespeed;
		GE161::Game::sendEvent("COLLIDE");
		bounceCount_++;
	}
	if (ball->getY() < 0)
	{
		y_delta = (rand() % 3 + 1)*Ballmovespeed;
		GE161::Game::sendEvent("COLLIDE");
		bounceCount_++;
	}
	if (ball->getX() < 0)
	{
		x_delta = (rand() % 3 + 1)*Ballmovespeed;
		GE161::Game::sendEvent("COLLIDE");
		bounceCount_++;
	}
	if (ball->getX() + frameWidth_ >= theGame->window()->clientWidth())
	{
		x_delta = -(rand() % 3 + 1)*Ballmovespeed;
		GE161::Game::sendEvent("GOAL");
		right_bounced_out_++;
	}
	if (ball->getY() + frameHeight_ >= theGame->window()->clientHeight())
	{
		y_delta = -(rand() % 3 + 1)*Ballmovespeed;
		GE161::Game::sendEvent("COLLIDE");
		bounceCount_++;
	}

	//if (bounceCount_ < 10)
	//{
	//	return GE161::Game::CONTINUE_SCENE;
	//}
	//else     // bounced out
	//{
	//	return -1;  // stop game
	//}


	//Using new created private "exitRequested" to handle exit event
	if (exitRequested)
		return -1;
	if (right_bounced_out_ >=10)
		return -1;

	return GE161::Game::CONTINUE_SCENE;
}

//created onEvent function to handle events with registerAsListener() function in setup
void PongGamePlayScene::onEvent(GE161::Event& event)
{
	if (event.type == GE161::Event::KEY_DOWN)  // this test isn't necessary
	{
		if (event.key == "X")
			exitRequested = true;
		else if (event.key == "W"){
			if (paddle1->getY() > 0)
				paddle1->moveY(-paddleSpeed);
		}
		else if (event.key == "S"){
			if (paddle1->getY() < theGame->window()->clientHeight() - paddleHeight_)
				paddle1->moveY(paddleSpeed);
		}
		else if (event.key == "UP"){
			if (paddle2->getY() > 0)
				paddle2->moveY(-paddleSpeed);
		}
		else if (event.key == "DOWN"){
			if (paddle2->getY() < theGame->window()->clientHeight() - paddleHeight_)
				paddle2->moveY(paddleSpeed);
		}
		else if (event.key == "BACKSPACE"){
			ball->setPos((theGame->window()->clientWidth() - frameWidth_) / 2, (theGame->window()->clientHeight() - frameHeight_) / 2);
		}
		else if (event.key == "F"){
			flame->enable_sprites(true);
		}
		else if (event.key == "L"){
			if (bolt->get_draw_state() == false){
				bolt->setPos(paddle1->getX(), paddle1->getY());
				bolt->enable_sprites(true);
			}
		}
		else if (event.key == "B"){
			blood->enable_sprites(true);
		}
	}
	else if (event.type == GE161::Event::CUSTOM_EVENT)  //CUSTOM_EVENT = 0
	{
		if (event.key == "COLLIDE")
		{
			blast->setPos(ball->getX(), ball->getY());
			blast->enable_sprites(true);
		}
		else if (event.key == "GOAL")
		{
			goal->setPos(ball->getX()-frameWidth_, ball->getY()-frameWidth_);
			goal->enable_sprites(true);
		}
		else if (event.key == "SMOKE")
		{
			ball->duration = 0;
			smoke->enable_sprites(false);
			paddleSpeed-=2;
		}
		else if (event.key == "FLAME")
		{
			flame->enable_sprites(false);
			paddleSpeed+=10;
		}
		else if (event.key == "BLOOD")
		{
			blood->enable_sprites(false);
			Ballmovespeed++;
		}
	}
}
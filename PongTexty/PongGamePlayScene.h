//PongGamePlayScene.h

#pragma once

#include "Pong.h"
#include "Scene.h"
#include "GameObject.h"
//include event.h to import Event object
#include "Event.h"
#include "Ball.h"
#include "paddle1.h"
#include "paddle2.h"
#include "blast.h"
#include "goal.h"
#include "smoke.h"
#include "flame.h"
#include "bolt.h"
#include "blood.h"

class PongGamePlayScene : public GE161::Scene
{
public:
	PongGamePlayScene(Pong* theGame);
	~PongGamePlayScene();

	bool setup();
	int draw();

	//added a void function to handle events
	void onEvent(GE161::Event& ev);

private:
	//added a new private to store the font
	Texty* text;

	Pong* theGame;

	std::vector<GE161::GameObject*> Entities;

	GE161::Ball* ball;
	//paddle object
	GE161::paddle1* paddle1;
	GE161::paddle2* paddle2;
	
	//added gameobjects
	GE161::blast* blast;
	GE161::goal* goal;
	GE161::smoke* smoke;
	GE161::flame* flame;
	GE161::bolt* bolt;
	GE161::blood* blood;

	int frameWidth_;
	int frameHeight_;
	//paddle size
	int paddleWidth_;
	int paddleHeight_;
	//blast sprite size
	int blastWidth_;
	int blastHeight_;
	//goal blast sprite size
	int goalWidth_;
	int goalHeight_;
	//smoke sprite size
	int smokeWidth_;
	int smokeHeight_;
	//flame sprite size
	int flameWidth_;
	int flameHeight_;
	//lightening bolt sprite
	int boltWidth_;
	int boltHeight_;
	//blood sprite
	int bloodWidth_;
	int bloodHeight_;

	int bounceCount_;

	int Ballmovespeed;
	int x_delta, y_delta;
	//smoke heading direction
	int smoke_x_delta, smoke_y_delta;
	//flame heading direction
	int flame_x_delta, flame_y_delta;
	//blood heading direction
	int blood_x_delta, blood_y_delta;
	//paddle move speed
	int paddleSpeed;

	bool exitRequested;
	//right side bounced out counter
	int right_bounced_out_;
};


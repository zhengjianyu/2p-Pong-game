
#include <string>
#include "Pong.h"
#include "PongInstructionsScene.h"
#include "PongGamePlayScene.h"

// Pong.cpp

//An object of the class derived from GE161::Game must be created.
Pong* theGame = new Pong();

// setup() is called once, before the window is created or displayed.
void Pong::setup()
{
	window()->size(500, 350);
	window()->title("Pong");

	addScene("Instructions", new PongInstructionsScene(this));
	addScene("GamePlay", new PongGamePlayScene(this));

	//default framerate here
	framerate_ = 30;
}

std::string Pong::chooseScene(std::string prevScene, int prevReturnCode)
{
	if (prevScene == START_GAME)
	{
		return "Instructions";
	}

	if (prevScene == "Instructions")
	{
		return "GamePlay";
	}

	// prevScene must == "GamePlay"
	return EXIT_GAME;
}



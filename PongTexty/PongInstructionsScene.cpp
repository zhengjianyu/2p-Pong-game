// PongInstructionScene.cpp

#include "PongInstructionsScene.h"

PongInstructionsScene::PongInstructionsScene(Pong* game) :
theGame(game)
{
}

PongInstructionsScene::~PongInstructionsScene()
{
	delete instructions;
}


bool PongInstructionsScene::setup()
{
	//get renderer from window;
	SDL_Renderer* renderer = theGame->getRenderer();
	//initialize text;
	text = new Texty(renderer, GE161::Game::basePath() + "FreeSans.ttf", 22, true);

	instructions = new GE161::GameObject(20, 20);
	GE161::Sprite* instructionsImage = new GE161::Sprite(450, 300);
	frameIndex = instructionsImage->makeFrame(GE161::Game::basePath() + "Instructions.png", 0, 0);
	instructions->attachSprite(instructionsImage);
	
	playGameRequested = false;
	exitRequested = false;

	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);
	
	GE161::Game::debugOut("PongInstructionsScene::setup completed!");
	return true;
}

int PongInstructionsScene::draw()
{
	//write!
	text->write("Avoid missing ball for high score.", 85, 80);
	text->write("Press space to start.\n    Press X to quit.", 145, 200);

	//instructions->draw(frameIndex);

	if (playGameRequested)
	{
		return 1;		// don't call draw again, go on to next scene
	}
	else if (exitRequested)
	{
		return -1;		// stop program
	}

	return GE161::Game::CONTINUE_SCENE;
}

void PongInstructionsScene::onEvent(GE161::Event& event)
{
	if (event.type == GE161::Event::KEY_DOWN)  // this test isn't necessary
	{
		if (event.key == " ")
			playGameRequested = true;
		else if (event.key == "X")
			exitRequested = true;
	}
}

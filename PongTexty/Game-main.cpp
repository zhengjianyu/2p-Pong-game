#include "Game.h"
#include "iostream"

void GE161::Game::main(int x)
{
	if (x != 8675309)
	{
		fatalSDLError("Do not invoke GE161::Game::main()");
		return;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fatalSDLError("SDL_Init(SDL_INIT_EVERYTHING) Error in main(): ", SDL_GetError());
		return;
	}

	//initialize TTF
	if (TTF_Init() != 0){
		fatalSDLError("TTF_Init() Error in main(): ", SDL_GetError());
		return;
	}

	//create custom event type
	//Uint32 USR_MAIN = SDL_RegisterEvents(3);
	//Uint32 USER_Event_1,USER_Event_2;
	//{
	//	Uint32 i = USR_MAIN;
	//	USER_Event_1 = ++i;
	//	USER_Event_2 = ++i;
	//}
	//SDL_Event event; event.type = USER_Event_1;
	//SDL_PushEvent(&event);


	// Invoke the game's overridden setup() method, and create the SDL window.
	window_ = new GE161::Window();
	setup();
	window_->initialize();
	window_->clearBackground();

	//set back ground color here
	window_->setBGcolor(255, 255, 255, SDL_ALPHA_OPAQUE);

	eventQueue_ = new GE161::EventQueue();

	std::string sceneName = GE161::Game::START_GAME;
	int returnCode = CONTINUE_SCENE;

	// Loop through the outer while loop once per scene.
	// A negative return code from a scene says "Stop the program!"
	while (returnCode >= 0)
	{
		// Ask the game which scene to do next.
		sceneName = GE161::Game::theGame->chooseScene(sceneName, returnCode);
		GE161::Scene* scene = GE161::Game::theGame->lookUpScene(sceneName);
		// Now we have the scene to use.  First, run its setup().
		bool success = scene->setup();
		if (!success)
		{
			fatalSDLError("error in main(), setup failed for scene", sceneName);
			return;
		}

		// setup() succeeded.  Run its draw() until a non-zero return code.
		returnCode = CONTINUE_SCENE;

		//create vector to store framerate in 4 secs
		std::vector<int> delayList;
		int counter = 0;
		// Loop through the inner while loop once per frame in scene.
		while (returnCode == CONTINUE_SCENE)
		{
			int ticks = getTicks();
			eventQueue_->getSDLEvents();
			eventQueue_->callEventListeners();

			window_->clearBackground();
			returnCode = scene->draw();

			window_->drawToScreen();
			//I have used lots of std::cout to debug instead of debugOut() for instant checking.
			//std::cout << framerate_ << " " << ticks << "  " << getTicks() << "     " << 1000/framerate_ + ticks - getTicks() << std::endl;
			delay(1000/framerate_ + ticks - getTicks());
			delayList.push_back(getTicks() - ticks);
		    counter += 1;
		    if (counter == 5){
				int result = 0;
				for (int i = 0; i < delayList.size(); i++){
					result += delayList[i];
				}
				//debugOut
				debugOut("Average framerate in five seconds:" + std::to_string(result/5));
				counter = 0;
				delayList.clear();
			}
		}
		std::string m = std::string("return code from ") + sceneName + std::string(": ") + std::to_string(returnCode);
		debugOut(m);
	}

	SDL_Quit();
	return;
}
#include "Game.h"

const std::string GE161::Game::START_GAME = "*STARTGAME*";
const std::string GE161::Game::EXIT_GAME = "*EXITGAME*";

//The linker wants this static variable defined here; it will get
// its actual value in main().
GE161::Game* GE161::Game::theGame = nullptr; 

GE161::Game::Game()
{
	// Store a pointer to the game in a static variable for access by main().
	if (theGame == nullptr)
	{
		theGame = this;
	}
	else
	{
		fatalSDLError("More than one game object has been created.");
	}
}


GE161::Game::~Game()
{
}

void GE161::Game::addScene(std::string name, Scene* scene)
{
	sceneMap[name] = scene;

}

GE161::Scene* GE161::Game::lookUpScene(std::string name)
{
	if (sceneMap.count(name) == 1)
		return sceneMap[name];

	fatalSDLError("in Game::lookUpScene, scene name not found:", name);

	return nullptr;
}

SDL_Renderer* GE161::Game::getRenderer()
{
	return window_->sdl_renderer;
}

void GE161::Game::delay(int milliseconds)
{
	if (milliseconds <= 0)
		return;
	SDL_Delay(static_cast<unsigned int>(milliseconds));
}

std::string GE161::Game::pathSlash()
{
#ifdef _WIN32
	return std::string("\\");
#else
	return std::string("/");
#endif
}

int GE161::Game::getTicks()
{
	return static_cast<int>(SDL_GetTicks());
}

void GE161::Game::registerAsListener(int eventType, EventListener* listener)
{
	theGame->eventQueue_->registerAsListener(eventType, listener);
}



// Based on res_path.h.
std::string GE161::Game::basePath()
{
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty())
	{
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath)
		{
			baseRes = basePath;
			SDL_free(basePath);
		}
		else
		{
			fatalSDLError("error in Game::basePath", SDL_GetError());
			baseRes = "";
		}
	}
	return baseRes;
}

void GE161::Game::debugOut(std::string message)
{
	OutputDebugString((message + "\n").c_str());
}

GE161::Window* GE161::Game::window()
{
	return window_;
}


//added function which causes an Event object to be put on the EventQueue.
void GE161::Game::sendEvent(std::string event_name)
{
	theGame->eventQueue_->push_event(event_name);
}
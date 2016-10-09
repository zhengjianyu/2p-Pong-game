#pragma once

#include <string>
#include <map>
#include "Window.h"
#include "Scene.h"
#include "EventQueue.h"

//Using Texty.h from HW4
#include "Texty.h"

namespace GE161
{
	class Game
	{
		friend class Sprite;
		friend class GameObject;

	public:
		Game();
		~Game();

		// These functions are called by the game code.
		void addScene(std::string name, Scene* scene);
		Scene* lookUpScene(std::string name);
		Window* window();
		static void registerAsListener(int eventType, EventListener* listener);

		// Helpful functions exposed to the game programmer.
		static void delay(int milliseconds);
		static std::string pathSlash();
		static std::string basePath();
		static void debugOut(std::string);
		static int getTicks();

		// These functions have to be overridden by the game code.
		virtual void setup() = 0;
		virtual std::string chooseScene(std::string prevScene, int prevReturnCode) = 0;
		
		//Because override classes cannot change private variables,
		//I make this framerate parameter public to be changable by setup().
		//The default value of framerate is 30, which is set in Pong.cpp
		int framerate_;

		// This function should be called exactly once by main().
		void main(int x);

		static const std::string START_GAME;
		static const std::string EXIT_GAME;

		static Game* theGame;
		static const int CONTINUE_SCENE = 0;

		//move this private function to public
		SDL_Renderer* getRenderer();

		//Causes an Event object to be put on the EventQueue object,
		//making it static to be called without specify its relevant object
		static void sendEvent(std::string event_name);

	private:

		Window* window_;
		std::map<std::string, Scene*> sceneMap;
		EventQueue* eventQueue_;

	};

}

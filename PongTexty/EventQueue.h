#pragma once

#include <queue>
#include <vector>
#include <utility>
#include "Game.h"
#include "Event.h"

namespace GE161
{
	class EventQueue
	{
		friend class Game;

	public:
		EventQueue();
		~EventQueue();

		//added a function to be used in Game.h for adding event 
		void push_event(std::string event_name);

	private:
		void getSDLEvents();

		void registerAsListener(int eventType, EventListener* listener);

		void callEventListeners();

		std::queue<Event*> eventQueue_;

		std::vector<std::pair<int, EventListener*>> eventListenerList_;

	};

}


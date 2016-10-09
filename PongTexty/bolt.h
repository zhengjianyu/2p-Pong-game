#pragma once

#include "GameObject.h"

namespace GE161
{
	class bolt : public GameObject
	{
	public:
		bolt(int x_, int y_);
	
		void update();
		void setup(std::string basePath);
		//int get_frameWidth();
		//int get_frameHeight();

	private:
		int frameWidth_;
		int frameHeight_;

	};
}
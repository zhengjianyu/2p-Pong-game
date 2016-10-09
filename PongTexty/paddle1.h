#pragma once

#include "GameObject.h"

namespace GE161
{
	class paddle1 : public GameObject
	{
	public:
		paddle1(int x_, int y_);
	
		void update();
		void setup(std::string basePath);
		//int get_frameWidth();
		//int get_frameHeight();

	private:
		int frameWidth_;
		int frameHeight_;

	};
}
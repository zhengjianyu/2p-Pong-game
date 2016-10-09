#pragma once

#include <string>
#include "Sprite.h"

namespace GE161
{
	class GameObject
	{
	public:
		GameObject(int startingX = 0, int startingY = 0);
		~GameObject();

		void setPos(int x, int y);
		void moveX(int delta);
		void moveY(int delta);
		int getX();
		int getY();
		void attachSprite(Sprite* sprite);
		void draw(int frameIndex);
		void draw(std::string sequenceName);

		bool overlapsWith(GameObject& otherGameObject);

		//added function to return its private: sprite_
		Sprite* get_sprite();
		//added function to decide whether draw sprites on the screen
		void enable_sprites(bool TF);
		//added public variable to control its duration
		int duration;
		//added function to return its start_draw_ state
		bool get_draw_state();

		//added function to be overwritten by other entities.
		virtual void update();
		//added function to set up the gameobject
		virtual void setup(std::string basePath);
		//return frameWidth and frameHeight of the gameobject
		//virtual int get_frameWidth();
		//virtual int get_frameHeight();

	private:
		int x_;		// current position of
		int y_;		// this game object
		Sprite* sprite_;
		bool start_draw_;
	};

}


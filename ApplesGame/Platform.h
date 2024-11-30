#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Platform : public GameObject
	{
	public:
		Platform(const sf::Vector2f& position);
		void update(float timeDelta);
		bool getCollision(std::shared_ptr<GameObject> gameObject);
		bool checkCollisionWithBall(std::shared_ptr<GameObject> gameObject);

	private:
		void move(float speed);
	};
}



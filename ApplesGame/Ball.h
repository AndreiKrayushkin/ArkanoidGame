#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball : public GameObject
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;
		void update(float timeDelta);

		void invertDirectionX();
		void invertDirectionY();
		void changeAngle(float angle);
	private:
		sf::Vector2f direction;
		float lastAngle = 90;
	};
}



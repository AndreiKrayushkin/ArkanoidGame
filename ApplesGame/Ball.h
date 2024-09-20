#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Ball
	{
	public:
		void initBall();
		void updateBall(float timeDelta);
		void contactWithPlatform();
		void drawBall(sf::RenderWindow& window);

		const sf::Vector2f& getPosition() const { return sprite.getPosition(); }
		const sf::FloatRect& getRect() const { return sprite.getGlobalBounds(); }

	protected:
		sf::Sprite sprite;
		sf::Texture texture;

	private:
		sf::Vector2f direction;
	};
}



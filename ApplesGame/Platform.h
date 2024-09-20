#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Ball;

	class Platform
	{
	public:
		void initPlatform();
		void updatePlatform(float timeDelta);
		bool checkCollisionWithBall(const Ball& ball);
		void drawPlatform(sf::RenderWindow& window);

		const sf::Vector2f& getPosition() const { return sprite.getPosition(); }
		const sf::FloatRect& getRect() const { return sprite.getGlobalBounds(); }

	protected:
		sf::Sprite sprite;
		sf::Texture texture;

	private:
		void movePlatform(float speed);
	};
}



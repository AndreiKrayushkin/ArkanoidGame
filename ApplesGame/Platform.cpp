#include "Platform.h"
#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>
#include <assert.h>

namespace ArkanoidGame
{
	void Platform::initPlatform()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "platform.png"));
		
		initSprite(sprite, PLATFORM_WIDTH, PLATFORM_HEIGHT, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f });
	}

	void Platform::updatePlatform(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			movePlatform(-timeDelta * PLATFORM_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			movePlatform(timeDelta * PLATFORM_SPEED);
		}
	}

	void Platform::movePlatform(float speed)
	{
		auto position = sprite.getPosition();
		position.x = std::clamp(position.x + speed, PLATFORM_WIDTH / 2.f, SCREEN_WIDTH  - PLATFORM_WIDTH / 2.f);
		sprite.setPosition(position);
	}

	bool Platform::checkCollisionWithBall(const Ball& ball)
	{
		auto sqr = [](float x) {
			return x * x;
		};
		
		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball.getPosition();
		if (ballPos.x < rect.left) {
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width) {
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= BALL_SIZE / 2.0;
	}
	void Platform::drawPlatform(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
}
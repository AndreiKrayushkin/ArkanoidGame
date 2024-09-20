#include <assert.h>
#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"

namespace ArkanoidGame
{
	void Ball::initBall()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "ball.png"));

		initSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f });

		const float angle = 45.f + rand() % 90;
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	void Ball::updateBall(float timeDelta)
	{
		const auto pos = sprite.getPosition() + BALL_SPEED * timeDelta * direction;
		sprite.setPosition(pos);

		if (pos.x <= 0 || pos.x >= SCREEN_WIDTH) {
			direction.x *= -1;
		}

		if (pos.y <= 0 || pos.y >= SCREEN_HEIGHT) {
			direction.y *= -1;
		}
	}

	void Ball::contactWithPlatform()
	{
		direction.y *= -1;
	}

	void Ball::drawBall(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
}
#include <assert.h>
#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"

namespace ArkanoidGame
{
	Ball::Ball(const sf::Vector2f& position)
		: GameObject(TEXTURES_PATH + "ball.png", position, BALL_SIZE, BALL_SIZE)
	{
		const float angle = 90;
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	void Ball::update(float timeDelta)
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

	void Ball::invertDirectionX()
	{
		direction.x *= -1;
	}

	void Ball::invertDirectionY()
	{
		direction.y *= -1;
	}

	void Ball::changeAngle(float angle)
	{
		lastAngle = angle;
		const auto pi = std::acos(-1.f);
		direction.x = (angle / abs(angle)) * std::cos(pi / 180.f * angle);
		direction.y = -1 * abs(std::sin(pi / 180.f * angle));
	}
}
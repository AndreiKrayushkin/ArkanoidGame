#include "Platform.h"
#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>
#include <assert.h>

namespace ArkanoidGame
{
	Platform::Platform(const sf::Vector2f& position)
		: GameObject(TEXTURES_PATH + "platform.png", position, PLATFORM_WIDTH, PLATFORM_HEIGHT)
	{}

	void Platform::update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			move(-timeDelta * PLATFORM_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			move(timeDelta * PLATFORM_SPEED);
		}
	}

	bool Platform::getCollision(std::shared_ptr<GameObject> gameObject)
	{
		auto ball = std::dynamic_pointer_cast<Ball>(gameObject);
		if (!ball) return false;

		auto sqr = [](float x) {
			return x * x;
			};
		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball->getPosition();
		if (ballPos.x < rect.left) {
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width) {
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= BALL_SIZE / 2.0;
	}

	void Platform::move(float speed)
	{
		auto position = sprite.getPosition();
		position.x = std::clamp(position.x + speed, PLATFORM_WIDTH / 2.f, SCREEN_WIDTH  - PLATFORM_WIDTH / 2.f);
		sprite.setPosition(position);
	}

	bool Platform::checkCollisionWithBall(std::shared_ptr<GameObject> gameObject)
	{
		auto ball = std::dynamic_pointer_cast<Ball>(gameObject);
		if (!ball)
			return false;

		if (getCollision(ball)) {
			auto rect = getRect();
			auto ballPosInOlatform = (ball->getPosition().x - (rect.left + rect.width / 2)) / (rect.width / 2);
			ball->changeAngle(90 - 20 * ballPosInOlatform);
			return true;
		}
		return false;
	}
}
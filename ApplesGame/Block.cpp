#include <assert.h>
#include "Sprite.h"
#include "Block.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		: GameObject(TEXTURES_PATH + "platform.png", position, BLOCK_WIDTH, BLOCK_HEIGHT)
	{
		sprite.setColor(color);
	}

	Block::~Block()
	{
	}

	void Block::update(float timeDelta)
	{
	}

	bool Block::checkCollision(std::shared_ptr<GameObject> gameObject)
	{
		if (getCollision(gameObject))
		{
			isBroken = true;
			return true;
		}
		return false;
	}

	bool Block::isBrokenBlock() const
	{
		return isBroken;
	}

	bool Block::getCollision(std::shared_ptr<GameObject> gameObject) const
	{
		sf::Rect rect = gameObject->getRect();
		rect.width *= 1.1;
		return getRect().intersects(gameObject->getRect());
	}
}

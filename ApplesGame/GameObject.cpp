#include "Sprite.h"
#include <assert.h>
#include "GameObject.h"

namespace ArkanoidGame
{
	ArkanoidGame::GameObject::GameObject(const std::string& textureName, const sf::Vector2f& position, float width, float height)
	{
		auto res = texture.loadFromFile(textureName);
		assert(res);

		initSprite(sprite, width, height, texture);
		sprite.setPosition(position);
	}

	void GameObject::draw(sf::RenderWindow& window)
	{
		drawSprite(sprite, window);
	}
}

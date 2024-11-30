#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class GameObject
	{
	public:
		GameObject(const std::string& textureName, const sf::Vector2f& position, float width, float height);
		virtual ~GameObject() = default;

		virtual void update(float timeDelta) = 0;
		virtual void draw(sf::RenderWindow& window);

		const sf::Vector2f& getPosition() const { return sprite.getPosition(); }
		sf::FloatRect getRect() const { return sprite.getGlobalBounds(); }

	protected:
		sf::Sprite sprite;
		sf::Texture texture;
	};
}
#pragma once
#include <SFML/Graphics.hpp>

class GameStateData
{
public:
	virtual ~GameStateData() = default;

	virtual void init() = 0;
	virtual void handleWindowEvent(const sf::Event& event) = 0;
	virtual void update(float timeDelta) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};
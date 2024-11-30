#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateMainMenuData : public GameStateData
	{
	public:
		void init();
		void handleWindowEvent(const sf::Event& event);
		void update(float timeDelta);
		void draw(sf::RenderWindow& window);


	private:
		sf::Font font;
		Menu menu;
	};
}

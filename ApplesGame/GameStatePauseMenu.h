#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePauseMenuData
	{
	public:
		void init();
		void handleWindowEvent(const sf::Event& event);
		void update(float timeDelta);
		void draw(sf::RenderWindow& window);

	private:
		sf::Font font;

		sf::RectangleShape background;
		sf::Text titleText;

		Menu menu;
	};
}

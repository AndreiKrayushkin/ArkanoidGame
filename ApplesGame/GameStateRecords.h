#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateRecordsData : public GameStateData
	{
	public:
		void init();
		void handleWindowEvent(const sf::Event& event);
		void update(float timeDelta);
		void draw(sf::RenderWindow& window);

	private:
		sf::Font font;

		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;
	};
}

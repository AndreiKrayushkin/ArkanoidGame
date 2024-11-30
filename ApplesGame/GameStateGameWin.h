#pragma once
#include "SFML/Graphics.hpp"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateGameWin : public GameStateData
	{
	public:
		void init() override;
		void handleWindowEvent(const sf::Event& event) override;
		void update(float timeDelta) override;
		void draw(sf::RenderWindow& window) override;

	private:
		// Resources
		sf::Font font;

		float timeSinceGameWin = 0.f;

		// UI data
		sf::RectangleShape background;
		sf::Text gameWinText;
		sf::Text hintText;
	};
}

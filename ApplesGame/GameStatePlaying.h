#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;
	class Block;

	class GameStatePlayingData : public GameStateData
	{
	public:
		void init();
		void handleWindowEvent(const sf::Event& event);
		void update(float timeDelta);
		void draw(sf::RenderWindow& window);

	private:
		void createBlocks();
		void drawBlocks(sf::RenderWindow& window);
		void getBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY);

	private:
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Block>> blocks;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		sf::Sound gameOverSound;
	};
}

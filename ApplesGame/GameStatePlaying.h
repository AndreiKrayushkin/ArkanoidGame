#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData
	{
	public:
		void init();
		void handleWindowEvent(const sf::Event& event);
		void update(float timeDelta);
		void draw(sf::RenderWindow& window);

	private:
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		Platform platform;
		Ball ball;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		sf::Sound gameOverSound;
	};
}

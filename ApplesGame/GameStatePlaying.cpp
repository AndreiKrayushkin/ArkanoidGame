#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::init()
	{	
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(getTextOrigin(inputHintText, { 1.f, 0.f }));

		platform.initPlatform();
		ball.initBall();

		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::instance().getGame().pushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::update(float timeDelta)
	{
		platform.updatePlatform(timeDelta);
		ball.updateBall(timeDelta);

		const bool isCollision = platform.checkCollisionWithBall(ball);
		if (isCollision) {
			ball.contactWithPlatform();
		}

		const bool isGameFinished = !isCollision && ball.getPosition().y > platform.getRect().top;
		
		if (isGameFinished)
		{
			gameOverSound.play();
			
			Game& game = Application::instance().getGame();

			game.pushState(GameStateType::GameOver, false);
		}

	}

	void GameStatePlayingData::draw(sf::RenderWindow& window)
	{
		window.draw(background);

		platform.drawPlatform(window);
		ball.drawBall(window);

		scoreText.setOrigin(getTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}

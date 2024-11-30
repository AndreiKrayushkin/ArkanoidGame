#include "GameStatePlaying.h"
#include "Application.h"
#include "Block.h"
#include "Game.h"
#include "Text.h"
#include "GameSettings.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::init()
	{	
		auto fontRes = font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf");
		auto soundBufferRes = gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav");
		assert(fontRes);
		assert(soundBufferRes);

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

		gameObjects.emplace_back(std::make_shared<Platform>(sf::Vector2f({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f })));
		gameObjects.emplace_back(std::make_shared<Ball>(sf::Vector2f({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f })));
		createBlocks();

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
		static auto updateFunctor = [timeDelta](auto obj) { obj->update(timeDelta); };

		std::for_each(gameObjects.begin(), gameObjects.end(), updateFunctor);
		std::shared_ptr<Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);

		bool needInverseDirX = false;
		bool needInverseDirY = false;
		bool hasBrokeOneBlock = false;
		blocks.erase(
			std::remove_if(blocks.begin(), blocks.end(),
				[&hasBrokeOneBlock, &needInverseDirX, &needInverseDirY, this, ball](auto block) {
					if (!hasBrokeOneBlock && block->checkCollision(ball)) {
						hasBrokeOneBlock = true;
						const auto ballPos = ball->getPosition();
						const auto blockRect = block->getRect();

						getBallInverse(ballPos, blockRect, needInverseDirX, needInverseDirY);
					}
					return block->isBrokenBlock();
				}),
			blocks.end()
		);
		if (needInverseDirX) {
			ball->invertDirectionX();
		}
		if (needInverseDirY) {
			ball->invertDirectionY();
		}

		const bool isCollision = platform->checkCollisionWithBall(ball);

		const bool isGameFinished = !isCollision && ball->getPosition().y > platform->getRect().top;

		const bool isGameWin = blocks.size() == 0;
		Game& game = Application::instance().getGame();

		if (isGameWin) {
			game.pushState(GameStateType::GameWin, false);
		}

		if (isGameFinished)
		{
			gameOverSound.play();

			game.pushState(GameStateType::GameOver, false);
		}

	}

	void GameStatePlayingData::draw(sf::RenderWindow& window)
	{
		window.draw(background);

		static auto drawFunc = [&window](auto block) { block->draw(window); };
		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);

		drawBlocks(window);

		scoreText.setOrigin(getTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::createBlocks()
	{
		for (int row = 0; row < BLOCKS_COUNT_ROWS; ++row) {
			for (int col = 0; col < BLOCKS_COUNT_IN_ROW; ++col) {
				blocks.emplace_back(
					std::make_shared<Block>(
						sf::Vector2f({ BLOCK_SHIFT + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SHIFT), 100.f + row * BLOCK_HEIGHT }), 
						sf::Color::Green
					)
				);
			}
		}
	}

	void GameStatePlayingData::drawBlocks(sf::RenderWindow& window)
	{
		for (auto block : blocks)
		{
			if (!block->isBrokenBlock())
			{
				block->draw(window);
			}
		}
	}
	void GameStatePlayingData::getBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY)
	{
		if (ballPos.y > blockRect.top + blockRect.height)
		{
			needInverseDirY = true;
		}
		if (ballPos.x < blockRect.left)
		{
			needInverseDirX = true;
		}
		if (ballPos.x > blockRect.left + blockRect.width)
		{
			needInverseDirX = true;
		}
	}
}

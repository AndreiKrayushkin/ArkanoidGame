#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include "GameStateGameWin.h"

#include <assert.h>


namespace ArkanoidGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible)
		: type(type)
		, isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = std::make_unique<GameStateMainMenuData>();
			break;
		}
		case GameStateType::Playing:
		{
			data = std::make_unique<GameStatePlayingData>();
			break;
		}
		case GameStateType::GameOver:
		{
			data = std::make_unique<GameStateGameOverData>();
			break;
		}
		case GameStateType::GameWin:
		{
			data = std::make_unique<GameStateGameWin>();
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = std::make_unique<GameStatePauseMenuData>();
			break;
		}
		case GameStateType::Records:
		{
			data = std::make_unique<GameStateRecordsData>();
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
		if (data) {
			data->init();
		}
	}

	GameState::~GameState()
	{
		if (data) {
			data = nullptr;
		}
	}

	void GameState::update(float timeDelta)
	{
		data->update(timeDelta);
	}

	void GameState::draw(sf::RenderWindow& window)
	{
		data->draw(window);
	}

	void GameState::handleWindowEvent(sf::Event& event)
	{
		data->handleWindowEvent(event);
	}
}
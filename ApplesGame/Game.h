#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "GameSettings.h"
#include "GameState.h"
#include <unordered_map>

namespace ArkanoidGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void handleWindowEvents(sf::RenderWindow& window);
		bool updateGame(float timeDelta); // Return false if game should be closed
		void drawGame(sf::RenderWindow& window);
		void shutdown();

		bool isEnableOptions(GameOptions option) const;
		void setOption(GameOptions option, bool value);

		const RecordsTable& getRecordsTable() const { return recordsTable; }
		int getRecordByPlayerId(const std::string& playerId) const;
		void updateRecord(const std::string& playerId, int score);

		// Add new game state on top of the stack
		void pushState(GameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void popState();

		// Remove all game states from the stack and add new one
		void switchStateTo(GameStateType newState);

		
	private:
		std::vector<GameState> stateStack;
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;
	};
}

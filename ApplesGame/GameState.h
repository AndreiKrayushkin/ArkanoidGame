#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateData.h"


namespace ArkanoidGame
{

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		GameWin,
		ExitDialog,
		Records,
	};

	class GameState
	{
	public:
		GameState() = default;
		GameState(GameStateType type, bool isExclusivelyVisible);
		GameState(const GameState& state) = delete;
		GameState(GameState&& state) { operator=(std::move(state)); }

		~GameState();

		GameState& operator= (const GameState& state) = delete;
		GameState& operator= (GameState&& state) noexcept {
			type = state.type;
			data = std::move(state.data);
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;
			return *this;
		}

		GameStateType getType() const { return type; }
		bool isVisible() const { return isExclusivelyVisible; }

		template<class T>
		T* getData() const {
			return static_cast<T>(data);
		}

		void update(float timeDelta);
		void draw(sf::RenderWindow& window);
		void handleWindowEvent(sf::Event& event);

	private:
		GameStateType type = GameStateType::None;
		std::unique_ptr<GameStateData> data = nullptr;
		bool isExclusivelyVisible = false;
	};

}
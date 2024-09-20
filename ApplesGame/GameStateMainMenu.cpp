#include "GameStateMainMenu.h"
#include "Application.h"
#include "Game.h"
#include <assert.h>

namespace ArkanoidGame
{
	void GameStateMainMenuData::init()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		MenuItem startGame;
		startGame.text.setString("Start Game");
		startGame.text.setFont(font);
		startGame.text.setCharacterSize(24);
		startGame.onPressCallback = [](MenuItem&) {
			Application::instance().getGame().switchStateTo(GameStateType::Playing);
			};
		
		const bool isInfiniteApples = Application::instance().getGame().isEnableOptions(GameOptions::InfiniteApples);
		MenuItem optionsInfiniteApplesItem;
		optionsInfiniteApplesItem.text.setString("Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));
		optionsInfiniteApplesItem.text.setFont(font);
		optionsInfiniteApplesItem.text.setCharacterSize(24);
		optionsInfiniteApplesItem.onPressCallback = [](MenuItem& item) {
			Game& game = Application::instance().getGame();
			bool newOptionValue = !game.isEnableOptions(GameOptions::InfiniteApples);
			game.setOption(GameOptions::InfiniteApples, newOptionValue);
			item.text.setString("Infinite Apples: " + std::string(newOptionValue ? "On" : "Off"));
			};

		const bool isWithAcceleration = Application::instance().getGame().isEnableOptions(GameOptions::WithAcceleration);
		MenuItem optionsWithAccelerationItem;
		optionsWithAccelerationItem.text.setString("With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));
		optionsWithAccelerationItem.text.setFont(font);
		optionsWithAccelerationItem.text.setCharacterSize(24);
		optionsWithAccelerationItem.onPressCallback = [](MenuItem& item) {
			Game& game = Application::instance().getGame();
			bool newOptionValue = !game.isEnableOptions(GameOptions::WithAcceleration);
			game.setOption(GameOptions::WithAcceleration, newOptionValue);
			item.text.setString("With Acceleration: " + std::string(newOptionValue ? "On" : "Off"));
			};

		MenuItem options;
		options.text.setString("Options");
		options.text.setFont(font);
		options.text.setCharacterSize(24);
		options.hintText.setString("Options");
		options.hintText.setFont(font);
		options.hintText.setCharacterSize(48);
		options.hintText.setFillColor(sf::Color::Red);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;
		options.childrens.push_back(optionsInfiniteApplesItem);
		options.childrens.push_back(optionsWithAccelerationItem);
		
		MenuItem recordsItem;
		recordsItem.text.setString("Records");
		recordsItem.text.setFont(font);
		recordsItem.text.setCharacterSize(24);
		recordsItem.onPressCallback = [](MenuItem&) {
			Application::instance().getGame().pushState(GameStateType::Records, true);
			};

		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(font);
		yesItem.text.setCharacterSize(24);
		yesItem.onPressCallback = [](MenuItem&) {
			Application::instance().getGame().switchStateTo(GameStateType::None);
			};

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(font);
		noItem.text.setCharacterSize(24);
		noItem.onPressCallback = [this](MenuItem&) {
			menu.goBack();
			};

		MenuItem exitGameItem;
		exitGameItem.text.setString("Exit Game");
		exitGameItem.text.setFont(font);
		exitGameItem.text.setCharacterSize(24);
		exitGameItem.hintText.setString("Are you sure?");
		exitGameItem.hintText.setFont(font);
		exitGameItem.hintText.setCharacterSize(48);
		exitGameItem.hintText.setFillColor(sf::Color::Red);
		exitGameItem.childrenOrientation = Orientation::Horizontal;
		exitGameItem.childrenAlignment = Alignment::Middle;
		exitGameItem.childrenSpacing = 10.f;
		exitGameItem.childrens.push_back(yesItem);
		exitGameItem.childrens.push_back(noItem);

		MenuItem mainMenu;
		mainMenu.hintText.setString("Arkanoid Game");
		mainMenu.hintText.setFont(font);
		mainMenu.hintText.setCharacterSize(48);
		mainMenu.hintText.setFillColor(sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(recordsItem);
		mainMenu.childrens.push_back(exitGameItem);
		

		menu.initMenu(mainMenu);
	}

	void GameStateMainMenuData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				menu.goBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				menu.pressOnSelectedItem();
			}
			
			Orientation orientation = menu.getCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu.switchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
						orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu.switchToNextMenuItem();
			}
		}
	}

	void GameStateMainMenuData::update(float timeDelta)
	{

	}

	void GameStateMainMenuData::draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &menu.getCurrentContext().hintText;
		hintText->setOrigin(getTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		menu.drawMenu(window, viewSize / 2.f, { 0.5f, 0.f });
	}

}

#include "GameStateRecords.h"
#include "Application.h"
#include "Text.h"
#include "Game.h"
#include "GameSettings.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStateRecordsData::init()
	{
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		titleText.setString("RECORDS");
		titleText.setFont(font);
		titleText.setFillColor(sf::Color::Red);
		titleText.setCharacterSize(48);

		tableTexts.reserve(MAX_RECORDS_TABLE_SIZE);

		const Game& game = Application::instance().getGame();
		std::map<int, std::string> sortedRecordsTable;
		for (const auto& item : game.getRecordsTable())
		{
			sortedRecordsTable[item.second] = item.first;
		}

		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it) 
		{
			tableTexts.emplace_back();
			sf::Text& text = tableTexts.back();

			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}

		hintText.setString("Press ESC to return back to main menu");
		hintText.setFont(font);
		hintText.setFillColor(sf::Color::White);
		hintText.setCharacterSize(24);
	}

	void GameStateRecordsData::handleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::instance().getGame().popState();
			}
		}
	}

	void GameStateRecordsData::update(float timeDelta)
	{

	}

	void GameStateRecordsData::draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		titleText.setOrigin(getTextOrigin(titleText, { 0.5f, 0.f }));
		titleText.setPosition(viewSize.x / 2.f, 50.f);
		window.draw(titleText);

		std::vector<sf::Text*> textsList;
		textsList.reserve(tableTexts.size());
		for (auto& text : tableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { titleText.getGlobalBounds().left, viewSize.y / 2.f };
		drawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.f, 0.f });

		hintText.setOrigin(getTextOrigin(hintText, { 0.5f, 1.f }));
		hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(hintText);
	}

}
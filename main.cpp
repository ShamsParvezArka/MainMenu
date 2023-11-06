#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

enum class Menu
{
	continueGame, 
	newGame, 
	options, 
	quit
};

int main()
{
	const int windowWidth  = 960;
	const int windowHeight = 540;
	const std::string windowTitle = "Main Menu";
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle);

	const std::string backgourndTexturePath = "assets/image/background.png";
	const std::string indecatorTexturePath = "assets/image/indecator.png";
	const std::string textTexturePath = "assets/image/text.png";
	const std::string workshopTexturePath = "assets/image/workshop.png";

	sf::Texture backgroundTexture{};
	sf::Texture indecatorTexture{};
	sf::Texture textTexture{};
	sf::Texture workshopTexture{};

	if (!backgroundTexture.loadFromFile(backgourndTexturePath))
	{
		fmt::print("Error: cannot load texture from: {}\n", backgourndTexturePath);
		return -1;
	}

	if (!indecatorTexture.loadFromFile(indecatorTexturePath))
	{
		fmt::print("Error: cannot load texture from: {}\n", indecatorTexturePath);
		return -1;
	}
	if (!textTexture.loadFromFile(textTexturePath))
	{
		fmt::print("Error: cannot load texture from: {}\n", textTexturePath);
		return -1;
	}
	if (!workshopTexture.loadFromFile(workshopTexturePath))
	{
		fmt::print("Error: cannot load texture from: {}\n", workshopTexturePath);
		return -1;
	}

	sf::Sprite backgroundSprite{};
	sf::Sprite indecatorSprite{};
	sf::Sprite textSprite{};
	sf::Sprite workshopSprite{};
	
	backgroundSprite.setTexture(backgroundTexture);

	indecatorSprite.setTexture(indecatorTexture);
	float indecatorPositionX = 80.f;
	float indecatorPositionY = 130.f;
	indecatorSprite.setPosition(sf::Vector2f(indecatorPositionX, indecatorPositionY));

	textSprite.setTexture(textTexture);

	workshopSprite.setTexture(workshopTexture);
	float const workshopPositionX = 380.f;
	float const workshopPositionY = 76.f;
	workshopSprite.setPosition(sf::Vector2f(workshopPositionX, workshopPositionY));
	workshopSprite.setScale(2.f, 2.f);

	const std::string menuSelectionBufferPath = "assets/audio/select.wav";
	sf::SoundBuffer menuSelectionBuffer{};
	
	if (!menuSelectionBuffer.loadFromFile(menuSelectionBufferPath))
	{
		fmt::print("Error: cannot load sound buffer form: {}\n", menuSelectionBufferPath);
		return -1;
	}

	sf::Sound menuSelectionSound{};
	menuSelectionSound.setBuffer(menuSelectionBuffer);

	const std::string backgroundMusicPath = "assets/audio/background.wav";
	sf::Music backgroundMusic{};
	
	if (!backgroundMusic.openFromFile(backgroundMusicPath))
	{
		fmt::print("Error: cannot load music form: {}\n", menuSelectionBufferPath);
		return -1;
	}
	backgroundMusic.setVolume(50.f);
	backgroundMusic.play();

	sf::Font font;
	const std::string fontPath = "assets/font/fixedsys.ttf";
	if (!font.loadFromFile(fontPath))
	{
		fmt::print("Error: cannot load font from: {}\n", fontPath);
		return 1;
	} 

	sf::Text gameTitle("Game Name", font, 72);
	gameTitle.setFillColor(sf::Color::Black);
	float gameTitlePositionX = 550.f;
	float gameTitlePositionY = 64.f;
	gameTitle.setPosition(sf::Vector2f(gameTitlePositionX, gameTitlePositionY));

	sf::Text menuDescription("continue the game \nfrom where you left \nof.", font, 16);
	menuDescription.setFillColor(sf::Color::Black);
	float menuDescriptionPositionX = 73.f;
	float menuDescriptionPositionY = 340.f;
	menuDescription.setPosition(sf::Vector2f(menuDescriptionPositionX, menuDescriptionPositionY));

	int currentMenu = 0;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();	
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case (sf::Keyboard::Down):
					if (currentMenu < 3)
					{
						indecatorPositionY += 30.f;
						currentMenu++;
						menuSelectionSound.play();
					}
					indecatorSprite.setPosition(sf::Vector2f(indecatorPositionX, indecatorPositionY));
					break;
				case (sf::Keyboard::Up):
					if (currentMenu > 0)
					{
						indecatorPositionY -= 30.f;
						currentMenu--;
						menuSelectionSound.play();
					}
					indecatorSprite.setPosition(sf::Vector2f(indecatorPositionX, indecatorPositionY));
					break;
				case (sf::Keyboard::Enter):
					if (currentMenu == static_cast<int>(Menu::quit))
					{
						window.close();
					}
					break;
				default:
					continue;
				}

				if (currentMenu == static_cast<int>(Menu::continueGame))
				{
					menuDescription.setString("Continue the game \nfrom where you left \nof.");
				}
				if (currentMenu == static_cast<int>(Menu::newGame))
				{
					menuDescription.setString("Start a new game. \n\nAll of your previous \nprogress will be \nlost");
				}
				if (currentMenu == static_cast<int>(Menu::options))
				{
					menuDescription.setString("Tweak your game \nsettings.");
				}
				if (currentMenu == static_cast<int>(Menu::quit))
				{
					menuDescription.setString("Quit game. \n\nDon't worry, auto \nsave feature is on.");
				}
			}
		}
		window.clear();
		window.draw(backgroundSprite);
		window.draw(indecatorSprite);
		window.draw(textSprite);
		window.draw(workshopSprite);
		window.draw(menuDescription);
		window.draw(gameTitle);
		window.display();
	}

	return 0;
}

#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "TextureManager.hpp"
#include "consoleManager.h"
#include "JsonManager.h"
#include "Menu.h"

class Engine {
public:
	Engine();
	~Engine();

	const std::string version = "2.0";
	void loadGame();
	void windowEventMenager();
	void runEngine();
	void runMenu();

	enum GameState { APP_ERROR = 0 , LOADING = 1, MENU = 2, IN_GAME = 3 };
	GameState *gameState;

#if _DEBUG
	const std::string alphaVersion = "1.3";
#endif
private:
	ConsoleManager *consoleManager;
	JsonMenager *jsonMenager;

	sf::Vector2i minimalWindowResolution;
	sf::RenderWindow *window;
	TextureManager *textureManager;
	Menu* menu;
};
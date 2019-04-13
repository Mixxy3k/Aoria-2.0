#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include "JsonManager.h"
#include "TextureManager.hpp"

using namespace std;

class Menu : public sf::Drawable {
public:
	Menu(sf::RenderWindow* window, JsonMenager* jsonMenager, TextureManager* textureManager, ConsoleManager* consoleManager);
	~Menu();

	void menu();
	void resize(float X, float Y, float sX = 1.0f, float sY = 1.0f );

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	JsonMenager* jsonMenager;
	TextureManager* textureManager;
	ConsoleManager* consoleManager;
	sf::RenderWindow* window;
	sf::Sprite* background = new sf::Sprite;
	sf::Texture* bakgroundTexture = new sf::Texture;
	sf::Shader* shaderTest = new sf::Shader;
	sf::Clock time;

	sf::Vector2i windowResolution;
	struct button
	{
		sf::Text text;
		unsigned int defaultCharacterSize;
		bool customX = true;
		bool customY = true;
		bool clickable = false;
	};

	int sumOfButtons = 0;

	::map<int, button>* buttons = new ::map<int, button>;
	bool createButtons();
};
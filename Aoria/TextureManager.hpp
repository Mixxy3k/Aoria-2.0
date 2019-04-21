#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "ConsoleManager.h"

class TextureManager {
private:
	sf::Font font;

	std::map<int, sf::Texture> MapTexture;
	std::map<int, std::string> TextureList;
	ConsoleManager *consoleManager;
public:
	TextureManager(ConsoleManager *_consoleManager)
		:consoleManager (_consoleManager)
	{
		consoleManager->log("Texture Manager Loaded!", "MODULE LOG");
	}

	sf::Texture& getTexture(int id) 
	{ 
		try
		{
			return this->MapTexture.at(id);
		}
		catch (std::exception & e) 
		{
			this->consoleManager->errorExit(e.what());
			exit(-1); //just for shut up compilation warning
		}
	}

	//Load texture to ram, first parametr is name, second position in file and last is Identification Number(ID)
	bool loadTexture(const std::string &name, const std::string& position, const int& ID) {
		sf::Texture Texture;
		//If somthing go wrong
		if (!Texture.loadFromFile(position)) {
			//Error message
			consoleManager->errorExit("TODO - ERROR TEXTURE");
			TextureList[ID] = "ERROR_TEXTURE!";
			return false;
		}
		else {
			MapTexture[ID] = Texture;
			TextureList[ID] = name;
			this->consoleManager->log("TEXTURE MANAGER", "Loaded texture ID:", ID
				+ " [" + name + "] ", "Position: ", position);
			return true;
		}
	}
	
	void textureList() {
		for (auto elem : TextureList)
		{
			std::cout << "ID: " << elem.first << " Name: " << elem.second << std::endl;
		}
	}

	bool loadFont(const std::string& position) {
		if (font.loadFromFile(position)) {
			this->consoleManager->log("TEXTURE MANAGER", "Loaded font", position);
			return true;
		}
		return false;
	}

	sf::Font& getFont() 
	{
		try
		{
			return this->font;
		}
		catch (const std::exception &e)
		{
			consoleManager->errorExit(e.what());
		}
	}
};
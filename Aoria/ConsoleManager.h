#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#if _WIN64
	#include <Windows.h>
#endif

using namespace std;

class ConsoleManager {
public:
#if _DEBUG
	ConsoleManager(std::string version, std::string debugVersion, sf::RenderWindow *window);
#else
	ConsoleManager(std::string version, sf::RenderWindow* window);
#endif // _DEBUG
	~ConsoleManager();

	void hideConsole();
	void showConsole();

	void log(const string &message, const string &typeLog = "LOG");
	void debugLog(const string& message, const string& typeLog = "DEBUG LOG");
	void debugLog(const int& message, const string& typeLog = "DEBUG LOG");

	void seperator();
	void new_line(int lines = 1);


	void errorExit(string errorText);
private:
	string message;
	vector<string> *logs;
	sf::RenderWindow* window; /*Only for colse window if errorExit is used*/
};
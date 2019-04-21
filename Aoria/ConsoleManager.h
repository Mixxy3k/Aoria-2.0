#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdarg>
#include <sstream>
#if _WIN64
	#include <Windows.h>
#endif

using namespace std;

class ConsoleManager {
public:
#if _DEBUG
	ConsoleManager(const std::string& version, const std::string& debugVersion, sf::RenderWindow* window);
#else
	ConsoleManager(const std::string& version, sf::RenderWindow* window);
#endif // _DEBUG
	~ConsoleManager();

	void hideConsole();
	void showConsole();

	template <typename TypeLog, typename First, typename... Rest> void log(const TypeLog& typeLog, const First& first, const Rest& ... rest);
	template <typename First, typename... Rest> void debugLog(const First& first, const Rest& ... rest);
	template <typename First, typename... Rest> void moduleLog(const First& first, const Rest& ... rest);

	void ConsoleManager::errorExit(const std::string& errorText);

	void seperator();
	void new_line(int lines = 1);

private:
	template <typename T> void getLogAsString(const T& t);
	template <typename First, typename... Rest> void getLogAsString(const First& first, const Rest& ... rest);
	void saveToLogs();

	std::ostringstream message;
	std::vector<std::string> *logs;
	sf::RenderWindow* window; /*Only for colse window if errorExit is used*/
};

template<typename T>
inline void ConsoleManager::getLogAsString(const T& t) { this->message << " " << t; }

template<typename First, typename ...Rest>
inline void ConsoleManager::getLogAsString(const First& first, const Rest& ...rest)
{
	this->message << " " << first;
	getLogAsString(rest...);
}

template<typename TypeLog, typename First, typename ...Rest>
inline void ConsoleManager::log(const TypeLog& typeLog, const First& first, const Rest& ...rest)
{
	if (typeLog == "") 
		this->message << "LOG:";
	else
		this->message << typeLog << ":";

	getLogAsString(first, rest...);
#if _DEBUG
	cout << message.str() << endl;
#endif
	this->saveToLogs();
}

template<typename First, typename ...Rest>
inline void ConsoleManager::debugLog(const First& first, const Rest& ...rest)
{
	this->message << "DEBUG LOG:";
	getLogAsString(first, rest...);
	cout << message.str() << endl;

	//clear
	message.clear();
	message.str("");
}

template<typename First, typename ...Rest>
inline void ConsoleManager::moduleLog(const First& first, const Rest& ...rest)
{
	message << "MODULE LOG:";

	getLogAsString(first, rest...);
#if _DEBUG
	cout << message.str() << endl;
#endif
	this->saveToLogs();
}

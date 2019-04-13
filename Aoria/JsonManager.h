#pragma once
#include "nlohmann JSON Library/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include "ConsoleManager.h"

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;
using namespace std;

class JsonMenager {
public:
	JsonMenager(ConsoleManager *consoleManager);
	~JsonMenager();
	std::string getDataFromJson(const string jsonName, const std::string name, std::vector<string> subname = std::vector<string> {"TEST"}, bool onlyCheck = false);
	int getDataFromJsonAsInt(const string jsonName, const std::string name, std::vector<string> subname);
	sf::Color getColorFromJson(const string jsonName, const std::string name, std::vector<string> subname);
	bool loadAllJsons();

	string jsonOutOfRange = "OUT OF RANGE";

private:
	ConsoleManager *consoleManager;

	std::map<std::string, json> *jsons = new std::map<std::string, json>;
	std::vector<string>* criticalJsosn = new std::vector<string>{ "MENU" };

	std::fstream file;
	fs::path jsonsPath; 
};
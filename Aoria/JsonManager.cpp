#include "JsonManager.h"

JsonMenager::JsonMenager(ConsoleManager* _consoleManager)
	:consoleManager(_consoleManager), jsonsPath(fs::current_path() /= "jsons")
{
	this->mustBeJsosn->operator[]("Menu") = 0;


	if (!loadAllJsons()) {
		consoleManager->errorExit("JSON ERROR");
	}

	consoleManager->log("MODULE LOG", "JsonManager Created!");
}

JsonMenager::~JsonMenager()
{
	delete jsons;
	delete mustBeJsosn;
}

bool JsonMenager::loadAllJsons()
{
	int jsonsAmount = 0;
	bool findName = false;
	this->jsons->clear();

	//create an iterator for json files
	//watch for "jsonPath" folder
	//this->consoleManager->log("JSON LOG", "Searching for jsons in folder: " + jsonsPath.u8string());
	if (fs::is_directory(jsonsPath)) 
	{
		//watch all files in "jsonPatch" folder
		for (auto& p : fs::recursive_directory_iterator("jsons")) 
		{
			//search and load ".json" files
			if (p.path().u8string().find(".json") != std::string::npos) 
			{
				this->file.open(p);
				string name;
				json j;
				try
				{
					this->file >> j;
				}
				catch (json::exception & e)
				{
					this->consoleManager->errorExit(e.what());
				}
				for (auto &it = j.begin(); it != j.end(); ++it) {
					findName = false;
					if (it.key().find("module") != std::string::npos && findName == false) {
						try
						{
							jsonsAmount++;
							name = j["module"]["name"].get<std::string>();
							this->jsons->operator[](name) = j;
							this->consoleManager->log("Loaded json from file: " + fs::current_path().u8string() + "\\" +  p.path().u8string(), "JSON LOG");
							this->file.close();
							findName = true;
						}
						catch (json::exception &e)
						{
							this->consoleManager->new_line(); consoleManager->seperator();
							string a = " \"module\" : { \"name\" } -> "; //e.what() + "blweqeqdqw" not working, e.what() + a works... [Dont ask why!]
							this->consoleManager->log("Not loaded json " + name + " from file: " + fs::current_path().u8string() + "\\" + p.path().u8string(), "JSON LOG");
							this->consoleManager->errorExit(a + e.what());
							return false;
						}
						
					}
				}
				if (findName == false)
				{
					this->consoleManager->new_line(); consoleManager->seperator();
					this->consoleManager->log("JSON WARNING", "Cannot load: " + fs::current_path().u8string() + "\\" + p.path().u8string());
					this->consoleManager->log("JSON WARNING", "Please add { \"module\" : { \"name\": \"Module Name\" } } to repair a problem!");
					this->consoleManager->log("JSON WARNING", "For example: { \"module\" : { \"name\": \"Menu\" }");
					this->consoleManager->log("JSON WARNING", "Remember, for default game jsons first letter must be UPPERCASE!");
					this->consoleManager->seperator(); consoleManager->new_line();
				}
				file.close();
			}
		}
	}
	else
	{
		this->consoleManager->log("Folder \"" + jsonsPath.u8string() + "\" are not exist or is empty!", "JSON ERROR");
		this->file.close();
		return false;
	}
	return true;
}

std::string JsonMenager::getDataFromJson(const string jsonName, const std::string name, std::vector<string> subname, bool onlyCheck, bool asInt)
{
	json j = this->jsons->operator[](jsonName);
	bool findName = false;
	string s = jsonOutOfRange;
	auto jsonAsString = j.dump();
	auto subnameItems = subname.size();

	for (auto &it = this->jsons->operator[](jsonName).begin(); it != this->jsons->operator[](jsonName).end(); ++it) {
		if (!it.key().compare(name))
		{
			s = "NO VALUE!";
			//I know... ;-;
			if (jsonAsString.find(subname.back()) != std::string::npos)
			{

				if (subnameItems == 1) 
				{
					if (!asInt)
					{
						try {
							s = j[name][subname.back()].get<std::string>();
						}
						catch (std::exception& e) {
							this->consoleManager->errorExit(e.what());
						}
					}
					else 
					{
						try {
							s = std::to_string(j[name][subname.back()].get<int>());
						}
						catch (std::exception& e) {
							this->consoleManager->errorExit(e.what());
						}
					}
				}
				else if (subnameItems == 2) 
				{
					if (!asInt)
					{
						try {
							s = j[name][(&subname.back())[-1]][subname.back()].get<std::string>();
						}
						catch (std::exception& e) {
							this->consoleManager->errorExit(e.what());
						}
					}
					else
					{
						try {
							s = std::to_string(j[name][(&subname.back())[-1]][subname.back()].get<int>());
						}
						catch (std::exception& e) {
							this->consoleManager->errorExit(e.what());
						}
					}
				}
				else if (subnameItems == 3) 
				{
					if (!asInt)
					{
						try {
							s = j[name][(&subname.back())[-2]][(&subname.back())[-1]][subname.back()].get<std::string>();
						}
						catch (std::exception& e) {
							this->consoleManager->errorExit(e.what());
						}
					}
					else
					{
						try {
							s = std::to_string(j[name][(&subname.back())[-2]][(&subname.back())[-1]][subname.back()].get<int>());
						}
						catch (std::exception& e) {
							this->consoleManager->errorExit(e.what());
						}
					}
				}
				else if (subnameItems == 4) 
				{
					if (!asInt)
					{
						try {
							s = j[name][(&subname.back())[-3]][(&subname.back())[-2]][(&subname.back())[-1]]
								[subname.back()].get<std::string>();
						}
						catch (std::exception& e) {
							this->consoleManager->errorExit(e.what());
						}
					}
					else
					{
						try {
							s = std::to_string(j[name][(&subname.back())[-3]][(&subname.back())[-2]][(&subname.back())[-1]]
								[subname.back()].get<int>());
						}
						catch (std::exception& e) {
							this->consoleManager->errorExit(e.what());
						}
					}
				}
				else
				{
					this->consoleManager->log("JSON Tree is to big!", "JSON WARNING!");
				}
			}
		}
	}
	//If name is not finded!
	if (s == jsonOutOfRange && onlyCheck == false)
		this->consoleManager->log("JSON WARNING", "Cannot find \"" + name + "\" in " + jsonName);
	return s;
}

int JsonMenager::getDataFromJsonAsInt(const string jsonName, const std::string name, std::vector<string> subname)
{
	int get = NULL;

	try
	{
		get = std::stoi(getDataFromJson(jsonName, name, subname, false, true));
	}
	catch (std::invalid_argument const& e)
	{
		this->consoleManager->errorExit(e.what());
	}
	catch (std::out_of_range const& e)
	{
		this->consoleManager->errorExit(e.what()); 
	}

	return get;
}

sf::Color JsonMenager::getColorFromJson(const string jsonName, const std::string name, std::vector<string> subname)
{
	string color = getDataFromJson(jsonName, name, subname);
	if (color == "white")
		return sf::Color::White;
	if (color == "cyan")
		return sf::Color::Cyan;
	if (color == "red")
		return sf::Color::Red;

	this->consoleManager->log("WARRING", "Unknow color: ", color, " -> used color \"white\"");
	return sf::Color::White;
}

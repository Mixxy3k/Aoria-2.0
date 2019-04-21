#include "ConsoleManager.h"

#if _DEBUG
ConsoleManager::ConsoleManager(const std::string& version, const std::string& debugVersion, sf::RenderWindow* window)
	: logs(new std::vector<std::string>)
{
	this->window = window;
	//Shut up SFML errors
	sf::err().rdbuf(NULL);
	showConsole();
	log("MODULE LOG", "Aoria v", version, "Alpha: ", debugVersion);
	log("MODULE LOG", "Console Manager Loaded!");

	int a = 1;
	debugLog("VARIABLE", a, "20");
}
#else
ConsoleManager::ConsoleManager(const std::string& version, sf::RenderWindow* window)
	: logs(new vector<string>)
{
	this->window = window;

	sf::err().rdbuf(NULL);
	hideConsole();
	log("Aoria v: " + version, "");
}
#endif // _DEBUG

ConsoleManager::~ConsoleManager()
{
	std::ofstream outFile("Logs.txt");
	log("MODULE LOG", "Console & Log manager stopped");
	for (const auto& e : *logs) outFile << e << "\n";
	outFile.close();
	if(logs != NULL) delete logs;
}

void ConsoleManager::seperator()
{
	std::cout << "-----------------------------------" << std::endl;
}

void ConsoleManager::new_line(int lines)
{
	if (lines < 1)
	{
		std::cout << std::endl;
		log("WARNING", "Cannot create a", lines, "lines");
		std::cout << std::endl;
		return;
	}
	for (auto i = 0; i < lines; i++) 
		std::cout << std::endl;
}

/* TODO
	TEAMPLATE!
*/
void ConsoleManager::errorExit(const std::string & errorText)
{
	//*gameState = APP_ERROR;
	window->close();
#if (_DEBUG == false)
	showConsole();
#endif
	log("ERROR", errorText);
	system("pause");
}

void ConsoleManager::saveToLogs()
{
	this->logs->emplace_back(message.str());
	message.clear();
	message.str("");
}

#if  _WIN64
void ConsoleManager::hideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ConsoleManager::showConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_RESTORE);
}
#else //Currently Aoria dont support Linux based system!
void consoleManager::hideConsole()
{
	system(disdown)
}

void consoleManager::showConsole()
{
	system(gnome-terminal);
}
#endif // _WIN64
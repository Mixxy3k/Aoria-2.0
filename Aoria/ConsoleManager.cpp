#include "ConsoleManager.h"

#if _DEBUG
ConsoleManager::ConsoleManager(std::string version, std::string debugVersion, sf::RenderWindow* window)
	:message(), logs(new vector<string>)
{
	this->window = window;
	//Shut up SFML errors
	sf::err().rdbuf(NULL);
	showConsole();
	log("Aoria v" + version + " DEBUG BUILD " + debugVersion, "");
	log("Console Manager Loaded!", "MODULE LOG");
}
#else
ConsoleManager::ConsoleManager(std::string version, sf::RenderWindow* window)
	:message(), logs(new vector<string>)
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
	log("Application stoped");
	for (const auto& e : *logs) outFile << e << "\n";
	outFile.close();
	if(logs != NULL) delete logs;
}

void ConsoleManager::log(const string & message, const string & typeLog)
{
	if (typeLog.empty())
		this->message = "LOG: " + message;

	else
		this->message = typeLog + ": " + message;

	//Prepare log to save to file
	logs->push_back(this->message);

	//  { If DEBUG -> Write log to console
	//	{ If RELASE -> Silent please
#if _DEBUG
	cout << this->message << endl;
#endif // _DEBUG
}

void ConsoleManager::debugLog(const string& message, const string& typeLog)
{
#if _DEBUG
	log(message, typeLog);
#endif // _DEBUG
}

void ConsoleManager::debugLog(const int& message, const string& typeLog)
{
#if _DEBUG
	log(std::to_string(message), typeLog);
#endif // _DEBUG
}

void ConsoleManager::seperator()
{
	cout << "-----------------------------------" << endl;
}

void ConsoleManager::new_line(int lines)
{
	if (lines < 1)
	{
		cout << endl;
		log("Cannot create a " + to_string(lines) +" lines", "WARNING");
		cout << endl;
		return;
	}
	for (auto i = 0; i < lines; i++) 
		cout << endl;
}

void ConsoleManager::errorExit(string errorText)
{
	//*gameState = APP_ERROR;
	window->close();
#if (_DEBUG == false)
	showConsole();
#endif
	log(errorText, "ERROR");
	system("pause");
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
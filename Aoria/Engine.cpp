#include "Engine.h"

#if _DEBUG
/*Create engine class in debug mode, its allow app to:
	- Show Console
	- Read Logs and Errors
*/
Engine::Engine()
{
	this->gameState = new GameState;
	this->window = new sf::RenderWindow();

	*gameState = LOADING;
	/* Set window resolution to 1024x512 */
	this->minimalWindowResolution = sf::Vector2i(1024, 512);
	/* Creating a window and set title fo relase mode */
	this->window->create(sf::VideoMode(minimalWindowResolution.x, minimalWindowResolution.y), "Aoria " + version, sf::Style::Default);
	/* Change tilte of window for debug mode */
	this->window->setTitle("Aoria " + version + " Alpha: " + alphaVersion);

	this->consoleManager = new ConsoleManager(version, alphaVersion, window);

	this->textureManager = new TextureManager(consoleManager);
	this->jsonMenager = new JsonMenager(consoleManager);
}
#else
/*Create engine class in debug mode. Features:
	- Hide Console
	- [NOT IN GAME YET]Log into file

*/
Engine::Engine()
{
	this->gameState = new GameState;
	this->window = new sf::RenderWindow();

	*gameState = LOADING;
	/* Set window resolution to 1024x512 */
	this->minimalWindowResolution = sf::Vector2i(1024, 512);
	/* Creating a window and set title fo relase mode */
	this->window->create(sf::VideoMode(minimalWindowResolution.x, minimalWindowResolution.y), "Aoria " + version, sf::Style::Default);
	
	this->consoleManager = new ConsoleManager(version, window);

	this->textureManager = new TextureManager(consoleManager);
	this->jsonMenager = new JsonMenager(consoleManager);
}
#endif

Engine::~Engine() {
	delete this->textureManager;
	delete this->menu;
	delete this->window;
	delete this->gameState;
	delete this->consoleManager;
	cout << "Ram Cleared!" << endl;
}

void Engine::loadGame()
{
	this->consoleManager->seperator();
	this->consoleManager->log("Loading font and textures!");
	this->consoleManager->new_line();

	//Load font to memory
	this->textureManager->loadFont("data/Fonts/good times/good times rg.ttf");

	//Display a Loading message, set window color to black
	//Create a object for Loading message
	sf::Text loadingText("Loading", textureManager->getFont(), 90);
	loadingText.setPosition(window->getSize().x / 2 - loadingText.getGlobalBounds().width / 2, window->getSize().y / 2 - loadingText.getGlobalBounds().height / 2);
	this->window->clear();
	this->window->draw(loadingText);
	this->window->draw(loadingText);
	this->window->display();


	//Loading a texture
	this->textureManager->loadTexture("tile", "data/tile.png", 101);

	this->textureManager->loadTexture("background", "data/background-1409125_1280.png", 0);
	this->textureManager->loadTexture("player", "data/Player/ship.png", 1);
	this->textureManager->loadTexture("blueShip", "data/Si/bluemoob.png", 2);
	this->textureManager->loadTexture("kineticBullet", "data/Kinetic/Kinetic.png", 3);
	this->textureManager->loadTexture("topLeftBar", "data/Bar/Top Left Bar.png", 4);
	this->textureManager->loadTexture("topRightBar", "data/Bar/Top Right Bar.png", 5);
	this->textureManager->loadTexture("laser", "data/Laser/Laser.png", 6);
	this->consoleManager->seperator();
	this->consoleManager->log("All loaded succesful!");
	this->menu = new Menu(window, jsonMenager, textureManager, consoleManager);

	*gameState = MENU;
	runMenu();
}

void Engine::windowEventMenager()
{
	sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();

			if (event.type == sf::Event::Resized)
			{
				if ((int)event.size.width <= this->minimalWindowResolution.x)
					this->window->setSize(sf::Vector2u(minimalWindowResolution.x, this->window->getSize().y));
				if ((int)event.size.height <= this->minimalWindowResolution.y)
					this->window->setSize(sf::Vector2u(this->window->getSize().x, minimalWindowResolution.y));

				this->window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)this->window->getSize().x, (float)this->window->getSize().y)));

				float sX = (float)this->window->getSize().x / minimalWindowResolution.x;
				float sY = (float)this->window->getSize().y / minimalWindowResolution.y;
				this->menu->resize(-1, -1, sX, sY);
			}
		}
}

void Engine::runEngine()
{
	while (*gameState == IN_GAME && this->window->isOpen())
	{
		windowEventMenager();
	}
}

void Engine::runMenu()
{
	while (*gameState == MENU && this->window->isOpen()) 
	{
		windowEventMenager();
		this->window->clear();
		this->window->draw(*menu);
		this->window->display();

		Sleep(10);
	}
}
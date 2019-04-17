#include "Menu.h"

Menu::Menu(sf::RenderWindow* window, JsonMenager* jsonMenager, TextureManager* textureManager, ConsoleManager* consoleManager)
{
	this->window = window;
	this->jsonMenager = jsonMenager;
	this->textureManager = textureManager;
	this->consoleManager = consoleManager;
	this->consoleManager->log("Creating Menu");

	string moduleName = jsonMenager->getDataFromJson("Menu", "module", std::vector<string> {"fullName"});

	this->consoleManager->log("Json module name: " + moduleName);

	/*START Shader test*/
	if (!shaderTest->loadFromFile("data/shader_test.frag", sf::Shader::Fragment))
	{
		this->consoleManager->errorExit("Shaders not loaded! [shader test]");
	}
	this->consoleManager->log("Shaders loaded! [shader test]");
	/*END Shader test*/

	if (!this->createButtons()) {
		this->consoleManager->errorExit("Cannot load buttons from json!");
	}
	this->bakgroundTexture->operator=(this->textureManager->getTexture(101));
	this->bakgroundTexture->setRepeated(true);

	background->setTexture(*bakgroundTexture);
	background->setTextureRect({ 0,0,1024,512 });

	this->consoleManager->log("Menu created");
	time.restart();

}

Menu::~Menu()
{
	delete buttons;
	delete background;
}

void Menu::menu()
{
	return;
}
void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	shaderTest->setUniform("time", time.getElapsedTime().asSeconds());
	target.draw(*background, shaderTest);

	for (const auto& a : *buttons)
	{
		target.draw(a.second.text, states);
	}
	
}
void Menu::resize(float X, float Y, float sX, float sY)
{
	this->background->setTextureRect({ 0,0, (int)this->window->getSize().x, (int)this->window->getSize().y});
	for (const auto& a : *buttons)
	{
		if (!this->buttons->operator[](a.first).customX) {
			this->buttons->operator[](a.first).text.setPosition(X, this->buttons->operator[](a.first).text.getPosition().y);
		}
		if (!this->buttons->operator[](a.first).customY) {
			this->buttons->operator[](a.first).text.setPosition(Y, this->buttons->operator[](a.first).text.getPosition().x);
		}
		this->buttons->operator[](a.first).text.setCharacterSize((unsigned int)((float)this->buttons->operator[](a.first).defaultCharacterSize * sY));

		if (X == -1 && this->buttons->operator[](a.first).customX == false) {
			this->buttons->operator[](a.first).text.setPosition(this->window->getSize().x / 2.f - (int)this->buttons->operator[](a.first).text.getGlobalBounds().width / 2.f,
				this->buttons->operator[](a.first).text.getPosition().y);
		}
		if (Y == -1 && this->buttons->operator[](a.first).customY == false) {
			this->buttons->operator[](a.first).text.setPosition(this->buttons->operator[](a.first).text.getPosition().x,
				(float)a.first * this->buttons->operator[](a.first).text.getCharacterSize() * 8.f / sumOfButtons);
		}
	}
}
int Menu::userInput(sf::Event &event)
{
	sf::Vector2f mouse(sf::Mouse::getPosition(*window));
	int option = 0; //0 -> Nothing, 1-> Game, 2- > Game Reset, 3 -> Exit

	for (const auto& a : *buttons)
	{
		if (this->buttons->operator[](a.first).text.getGlobalBounds().contains(mouse) && this->buttons->operator[](a.first).clickable) 
		{
			this->buttons->operator[](a.first).text.setFillColor(sf::Color::Cyan);
			
			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) 
			{
				switch (a.first)
				{
				case 2:
					return 1;
				case 3:
					return 2;
				case 4:
					return 3;
				default:
					option = 0;
					break;
				}
			}

		}
		else this->buttons->operator[](a.first).text.setFillColor(sf::Color::White);
	}
	return 0;
}
bool Menu::createButtons()
{
	bool created = false;
	string base = "button";
	int numeration = 1;
	string combine = base + std::to_string(numeration);

	while (this->jsonMenager->getDataFromJson("Menu", combine, std::vector<string> { "TEST" }, true) != this->jsonMenager->jsonOutOfRange)
	{
		combine = base + std::to_string(++numeration);
		sumOfButtons++;
	}
	numeration = 1;
	combine = base + std::to_string(numeration);
	while (this->jsonMenager->getDataFromJson("Menu", combine, std::vector<string> { "TEST" }, true) != this->jsonMenager->jsonOutOfRange)
	{
		sf::Text text("TEXT", this->textureManager->getFont());
		created = true;

		text.setFont(this->textureManager->getFont());
		text.setCharacterSize(this->jsonMenager->getDataFromJsonAsInt("Menu", combine, std::vector<string> {"characterSize"}));
		text.setString(this->jsonMenager->getDataFromJson("Menu", combine, std::vector<string> {"buttonText"}));

		text.setPosition((float)this->jsonMenager->getDataFromJsonAsInt("Menu", combine, std::vector<string> {"position", "X"}),
			(float)this->jsonMenager->getDataFromJsonAsInt("Menu", combine, std::vector<string> {"position", "Y"}));
		
		if (text.getPosition().x == -1) {
			text.setPosition(this->window->getSize().x / 2.f - (int)text.getGlobalBounds().width / 2.f, text.getPosition().y);
			this->buttons->operator[](numeration).customX = false;
		}
		if (text.getPosition().y == -1) {
			text.setPosition(text.getPosition().x, (float)numeration * text.getCharacterSize()* 8.f/sumOfButtons);
			this->buttons->operator[](numeration).customY = false;
		}

		bool clickable = this->jsonMenager->getDataFromJsonAsInt("Menu", combine, std::vector<string> {"clickable"});

		this->buttons->operator[](numeration).text = text;
		this->buttons->operator[](numeration).defaultCharacterSize = text.getCharacterSize();
		this->buttons->operator[](numeration).clickable = clickable;

		this->consoleManager->log("Created button: ID " + std::to_string(numeration) + " [" + this->buttons->operator[](numeration).text.getString() + "]");

		combine = base + std::to_string(++numeration);
	}
	return created;
}
#include "MainMenuState.h"


/*Private functions*/

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Orbitron/Orbitron-Regular.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}


void MainMenuState::initKeybinds()
{
	//init keybinds from enginestate_keybinds.ini file
	std::ifstream ifs("Config/enginestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string keybind_name, key_name;

		while (ifs >> keybind_name >> key_name)
		{
			this->keybinds[keybind_name] = this->supportedKeys->at(key_name);
		}
	}
	ifs.close();
}

void MainMenuState::initButtons()
{
	sf::Color idleColor = sf::Color(70, 70, 100, 200);
	sf::Color hoverColor = sf::Color(80, 80, 120, 180);
	sf::Color activeColor = sf::Color(50, 50, 70, 200);

	/* Out od date
	this->buttons["ENGINE_BTN"] = new Button(200, 200, 150, 40,
		&this->font, "THULE ENGINE v0.1");
	this->buttons["MAINMENU_BTN"] = new Button(200, 270, 150, 40,
		&this->font, "MAIN MENU");
	this->buttons["EXITDESKTOP_BTN"] = new Button(200, 340, 150, 40,
		&this->font, "BACK TO DESKTOP");*/
}

/*Constructors Destructors*/

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color::White);
}


MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::endState()
{
	//do things at the end of the state, ex: save
	std::cout << "End of State\n";
}

void MainMenuState::updateInput(const float& delta)
{
	this->checkForQuitState();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->background.setFillColor(sf::Color::Yellow);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->background.setFillColor(sf::Color::White);
}

void MainMenuState::updateButtons()
{
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePosView);
	}

}

/*Functions*/
void MainMenuState::update(const float& delta)
{
	this->updateMousePositions();
	this->updateInput(delta);
	this->updateButtons();

}

void MainMenuState::renderButtons()
{
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->render(this->window);
	}
}

void MainMenuState::render()
{
	this->window->draw(this->background);
	this->renderButtons();
}



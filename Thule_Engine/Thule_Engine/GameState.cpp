#include "GameState.h"

/*Private functions*/

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Orbitron/Orbitron-Regular.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initKeybinds()
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

void GameState::initSystems()
{
	Sun* s = new Sun((float)300, (float)300);
	this->entities.push_back(s);
	Planet* p;
	for (int j = 2; j < 10; j++)
	{
		p = new Planet(s, (float)j * 300, 0);
		this->entities.push_back(p);
	}
	p = new Planet(p, (float)30, 0);
	this->entities.push_back(p);
}

void GameState::initView()
{
	this->zoom = 1.f;
	this->zoomTarget = this->zoom;
	this->initialWidth = 200.f;
	this->heightWidthRatio = (float)this->window->getSize().y / (float)this->window->getSize().x;

	this->mainView.setCenter(sf::Vector2f(300, 300));
	this->mainView.setSize(sf::Vector2f(this->initialWidth, this->initialWidth * heightWidthRatio));
}

/*Constructors Destructors*/
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
std::stack<unsigned char>* eventsPtr)
	: State(window, supportedKeys)
{
	this->clickTime = this->stateClock.getElapsedTime();
	this->initFonts();
	this->initKeybinds();
	this->initSystems();
	this->initView();

	this->eventsPtr = eventsPtr;

	this->UI = new GameUI(&this->font, this->eventsPtr);//share by pointer
}

GameState::~GameState()
{
	for (auto i = this->entities.begin(); i != this->entities.end();)
	{
		Entity* e = *i;
		delete e;
		i++;
	}

	delete this->UI;
}

/*Functions*/

void GameState::endEntity()
{
	//do things at the end of the state, ex: save
	std::cout << "End of State\n";
}

void GameState::updateInput(const float& delta)
{
	this->checkForQuitState();

	//Update key layouts
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->mainView.move(0.f, -100.f * this->zoom *delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->mainView.move(0.f, 100.f * this->zoom * delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->mainView.move(-100.f * this->zoom * delta, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->mainView.move(100.f * this->zoom * delta, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("A"))))
		if (this->mainView.getSize().x < 4000)
			this->zoomTarget += .1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("B"))))
		if (this->mainView.getSize().x > 100)
			this->zoomTarget -= .1f;
	this->window->setView(this->mainView);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->onViewDrag();
	}

}

void GameState::onWindowResize()
{
	this->initView();
	this->initUiView();
}

void GameState::onDubbleClick()
{

}

void GameState::onViewDrag()
{
		sf::Vector2f difference = this->window->mapPixelToCoords(this->mousePosWindow) - this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		this->mainView.move(difference);
		this->window->setView(this->mainView);
}

/*Mouse Events*/

void GameState::onMouseScroll(const float scrollDir, const float& delta)
{
	float zoomFactor = 10.0f;//zoom in out factor
	float upperLimit = 100.f, lowerLimit = 0.07f;

	if (scrollDir > 0)//zoom in
	{
		if (this->zoomTarget>this->zoom)//Stop zoom activity if the zoom is going opposite to the one to come
			this->zoomTarget = this->zoom;
		float inFactor = ((this->zoomTarget - lowerLimit) / (upperLimit - lowerLimit));
		this->zoomTarget -= zoomFactor * (1 - 1 / (5 * inFactor + 1));
	}
	else if (scrollDir < 0)//zoom out
	{
		if (this->zoomTarget < this->zoom)//Stop zoom activity if the zoom is going opposite to the one to come
			this->zoomTarget = this->zoom;
		float outFactor = ((upperLimit - this->zoomTarget) / (upperLimit - lowerLimit));
		this->zoomTarget += zoomFactor * ((1 - 1 / (10 * outFactor + 1)) + (1 + 1.111f / (outFactor - 1.111f)) / 10 );
	}
}

void GameState::onMouseMiddleClick()
{
}

void GameState::onMouseMiddleRelease()
{
}

void GameState::onMouseLeftClick()
{
	if (this->stateClock.getElapsedTime().asSeconds() - this->clickTime.asSeconds() > .3f)
	{
		this->clickTime = this->stateClock.getElapsedTime();
	}
	else
	{
		std::cout << "Doubble click! \n";
		this->onDubbleClick();
	}
}

void GameState::onMouseLeftRelease()
{
}

void GameState::onMouseRightClick()
{
}


void GameState::onMouseRightRelease()
{
}


/*Updaters and Renderers*/
void GameState::updateZoom()
{
	if (!isInRange(this->zoom, this->zoomTarget - .01f, this->zoomTarget + .01f))
	{
		//Position before zoom
		const sf::Vector2f beforeCoord{ this->mousePosView };

		//smooth zoom in
		this->zoom = lerp(.1f, this->zoom, this->zoomTarget);//zoom in
		sf::Vector2f newScale{ this->initialWidth * this->zoom,
			this->initialWidth * this->heightWidthRatio * this->zoom };
		this->mainView.setSize(newScale);

		this->window->setView(this->mainView);
		//Position after zoom
		const sf::Vector2f afterCoord{ this->window->mapPixelToCoords(this->mousePosWindow) };
		//Differcence between former position and new position
		sf::Vector2f difference = beforeCoord - afterCoord;

		this->mainView.move(difference);
	}
}

void GameState::update(const float& delta)
{
	this->updateInput(delta);
	this->updateMousePositions();
	this->updateZoom();

	for (auto i = this->entities.begin(); i != this->entities.end();)
	{
		Entity* e = *i;

		e->update(delta);
		//e->anim.update(delta);

		if (e->life == false) { i = this->entities.erase(i); delete e; }
		else i++;
	}

	this->UI->update((sf::Vector2f)this->mousePosWindow);
}

void GameState::render()
{
	this->window->setView(this->mainView);
	for (auto i : this->entities) i->render(this->window);

	this->window->setView(this->UiView); // define the UI view
	this->UI->render(this->window);

	this->window->setView(this->mainView); //set viewport to get data from it
}

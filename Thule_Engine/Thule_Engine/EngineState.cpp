#include "EngineState.h"

/*Private functions*/
void EngineState::initKeybinds()
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

void EngineState::initSystems()
{
		Sun* s = new Sun((float)300, (float)300);
		entities.push_back(s);
		for (int j = 2; j < 10; j++)
		{
			Planet* p = new Planet(s, (float)j * 30, 0);
			entities.push_back(p);
		}
}

void EngineState::initView()
{
	this->isMouseHold = false;
	float mainViewRatio = (float)this->window->getSize().y / (float)this->window->getSize().x;
	this->mainView.setCenter(sf::Vector2f(300, 300));
	this->mainView.setSize(sf::Vector2f(200, 200* mainViewRatio));
	this->minimapView.setSize(sf::Vector2f(500, 500* mainViewRatio));
	this->minimapView.setCenter(sf::Vector2f(300, 300));
	this->minimapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	
}

/*Constructors Destructors*/
EngineState::EngineState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->initKeybinds();
	this->initSystems();
	this->initView();
}

EngineState::~EngineState()
{
	for (auto i = entities.begin(); i != entities.end();)
	{
		SpaceEntity* e = *i;
		delete e;
		i++;
	}
}

/*Functions*/

void EngineState::endState()
{
	//do things at the end of the state, ex: save
	std::cout << "End of State\n";
}

void EngineState::updateInput(const float& delta)
{
	this->checkForQuitState();
	
	//Update key layouts
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->mainView.move(0.f, -100.f *delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->mainView.move(0.f, 100.f * delta);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->mainView.move(-100.f * delta, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->mainView.move(100.f * delta, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("A"))))
		if (this->mainView.getSize().x<4000)
			this->mainView.zoom(1.1f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("B"))))
		if (this->mainView.getSize().x>100)
			this->mainView.zoom(.9f);
	
	
	
}

void EngineState::onWindowResize()
{
	this->initView();
}

void EngineState::updateWindowDrag()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2f difference = this->window->mapPixelToCoords(this->mousePosWindow) - this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
		this->mainView.move(difference);
	}
}

void EngineState::onMouseScroll(signed char scrollDir, const float& delta)
{
	//focus on this part
	//Implement the lerp fuction form Source.h
	float mainViewWidt = this->mainView.getSize().x;
	float zoomFactor = 2.f;//the zoom out factor that is used to find the zoom in factor
	float upperLimit = 10000.f, lowerLimit = 50.f;


	if (scrollDir > 0)//zoom
	{
		float inFactor = ((lowerLimit - mainViewWidt) / (lowerLimit - upperLimit));
		//Position before zoom
		const sf::Vector2f beforeCoord{ this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)) };
		this->mainView.zoom(1 + (-1 + 1 / zoomFactor) * (1-1/(200*inFactor+1)));
		//need to set view to update (it is a copy of the view info)
		this->window->setView(this->mainView);
		//Position after zoom
		const sf::Vector2f afterCoord{ this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)) };
		
		sf::Vector2f difference = beforeCoord-afterCoord;

		this->mainView.move(difference);

		this->window->setView(this->mainView);
	}
	else if (scrollDir < 0)//zoom out
	{
		float outFactor = ((upperLimit - mainViewWidt) / (upperLimit - lowerLimit));
		//Position before zoom
		const sf::Vector2f beforeCoord{ this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)) };
		this->mainView.zoom(1+(zoomFactor-1) * outFactor);
		//need to set view to update (it is a copy of the view info)
		this->window->setView(this->mainView);
		//Position after zoom
		const sf::Vector2f afterCoord{ this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)) };

		sf::Vector2f difference = beforeCoord - afterCoord;

		this->mainView.move(difference);

		this->window->setView(this->mainView);
	}
}

void EngineState::update(const float& delta)
{
	
	this->updateInput(delta);
	this->updateWindowDrag();
	this->updateMousePositions();
	

	for (auto i = entities.begin(); i != entities.end();)
	{
		SpaceEntity* e = *i;

		e->update(delta);
		//e->anim.update(delta);

		if (e->life == false) { i = entities.erase(i); delete e; }
		else i++;
	}
}

void EngineState::render()
{
	this->window->setView(this->mainView);
	for (auto i : entities) i->render(this->window);
	
	
	/*sf::Vertex* path = NULL;
	int a = 200;
	path = new sf::Vertex[a];
	for (int q = 0; q < a; q++)
	{
		float angle = (q / (float)a) * PI;
		path[q] = sf::Vertex(sf::Vector2f(q*cos(angle)+400, q*sin(angle)+300));
		path[q].color = sf::Color(q, 255 - q, q, 200);
	}

	this->window->draw(path, a, sf::LineStrip);
	
	delete[] path;*/

	this->window->setView(this->minimapView);
	sf::RectangleShape background;
	background.setFillColor(sf::Color(44, 44, 44, 200));
	background.setPosition(sf::Vector2f(0, 0));
	background.setSize(sf::Vector2f(this->minimapView.getSize().x, this->minimapView.getSize().y));
	this->window->draw(background);
	
	for (auto i : entities) i->render(this->window);

	this->window->setView(this->mainView); //set viewport to get data from it
}

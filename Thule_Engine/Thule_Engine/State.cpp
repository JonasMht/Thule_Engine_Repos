#include "State.h"

/*Initialization*/

void State::initUiView()
{
	sf::Vector2f winDim{ (float)this->window->getSize().x, (float)this->window->getSize().y };
	this->UiView.setCenter(sf::Vector2f(winDim.x / 2, winDim.y / 2) );
	this->UiView.setSize(winDim);
	this->UiView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

/*Constructors Destructors*/

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	this->window = window;
	this->supportedKeys = supportedKeys; //copy pointer
	this->quitState = false;
	this->UI = NULL;

	this->initUiView();
}

State::~State()
{

}

/*Functions*/

void State::checkForQuitState()
{
	this->quitState = sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")));
}

const bool& State::getQuitState()
{
	return this->quitState;
}

/*Events*/
void State::endEntity()
{

}

void State::onWindowResize()
{
}

void State::onMouseScroll(const float scrollDir, const float& delta)
{
}

void State::onMouseMiddleClick()
{
}

void State::onMouseMiddleRelease()
{
}

void State::onMouseLeftClick()
{
}


void State::onMouseLeftRelease()
{
}

void State::onMouseRightClick()
{
}

void State::onMouseRightRelease()
{
}

/*Updaters and Renderers*/

void State::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	//this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

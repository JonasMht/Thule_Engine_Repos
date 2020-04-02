#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	this->window = window;
	this->supportedKeys = supportedKeys; //copy pointer
	this->quitState = false;
}

State::~State()
{

}

void State::checkForQuitState()
{
	this->quitState = sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")));
}

void State::endState()
{

}

void State::onWindowResize()
{
}

void State::onMouseScroll(signed char scrollDir, const float& delta)
{
}

void State::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	//this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

const bool& State::getQuitState()
{
	return this->quitState;
}
#include "GameUI.h"

/*Constructor Destructor*/

GameUI::GameUI(sf::Font* font)
{
	this->font = font;

	Button* b = new Button(100, 100, 100,100,font,"YES",sf::Color(0, 150, 255), sf::Color(85, 185, 255), sf::Color(0, 135, 230, 210));
	this->UiEntities.push_back(b);
}

GameUI::~GameUI()
{
	for (auto i = this->UiEntities.begin(); i != this->UiEntities.end();)
	{
		UiEntity* e = *i;
		delete e;
		i++;
	}
}

/*Updaters and Renderers*/

void GameUI::update(const sf::Vector2f& mousePosWindow)
{
	for (auto i : this->UiEntities) i->update(mousePosWindow);
}

void GameUI::render(sf::RenderTarget* target)
{
	for (auto i : this->UiEntities) i->render(target);
}

#include "GameUI.h"

/*Constructor Destructor*/

GameUI::GameUI(sf::Font *font, std::stack<unsigned char> *eventsPtr, sf::RenderWindow *window)
{
	this->font = font;

    this->window = window;
    sf::Vector2u winSize = window->getSize();

	UiEntity *b = new Button(.9f, 0.f, .1f, .1f,font, "Quit", eventsPtr, 0, this->window);
	this->UiEntities.push_back(b);

}

GameUI::~GameUI()
{
    std::list<UiEntity*>::iterator iterList;
	// Free pointers
    for (iterList = this->UiEntities.begin();
    iterList != this->UiEntities.end();
    iterList++)
    {
        delete (*iterList);
    }

   this->UiEntities.clear(); // List is deleted.
}

void GameUI::onWindowResize()
{
    for (auto i : this->UiEntities) i->onWindowResize();
}

/*Updaters and Renderers*/

void GameUI::update(const sf::Vector2f& mousePosWindow)
{
	for (auto i : this->UiEntities) i->update(mousePosWindow);
}

void GameUI::render(sf::RenderTarget *target)
{
	for (auto i : this->UiEntities) i->render(target);
}

#include "GameUI.h"

/*Constructor Destructor*/

GameUI::GameUI(sf::Font *font, std::stack<unsigned char> *eventsPtr)
{
	this->font = font;

	UiEntity *b = new Button(100, 100, 100,100,font,"Synth", eventsPtr, 0);
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

/*Updaters and Renderers*/

void GameUI::update(const sf::Vector2f& mousePosWindow)
{
	for (auto i : this->UiEntities) i->update(mousePosWindow);
}

void GameUI::render(sf::RenderTarget *target)
{
	for (auto i : this->UiEntities) i->render(target);
}

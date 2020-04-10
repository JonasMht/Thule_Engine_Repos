#ifndef UIENTITY_H
#define UIENTITY_H


#include "Entity.h"

class UiEntity
{
public:
	/*Variables*/
	sf::RenderWindow* window;

	/*Constructor Destructor*/
	UiEntity();
	virtual ~UiEntity();

	/*Functions*/
	virtual void onWindowResize() = 0;
	
	/*Updaters and Renderers*/
	virtual void update(const sf::Vector2f& mousePosWindow) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};


#endif // !UIENTITY_H

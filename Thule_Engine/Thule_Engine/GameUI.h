#ifndef GAMEUI_H
#define GAMEUI_H

#include "Button.h"

class GameUI :
	public UiEntity
{
public:
	/*Variables*/
	std::list<UiEntity*> UiEntities;
	sf::Font* font;

	/*Constructor Destructor*/
	GameUI(sf::Font* font);
	virtual ~GameUI();

	/*Updaters and Renderers*/
	void update(const sf::Vector2f& mousePosView);
	void render(sf::RenderTarget* target);
};

#endif // !GAMEUI_H
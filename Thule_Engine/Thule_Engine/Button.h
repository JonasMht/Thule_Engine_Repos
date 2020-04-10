#ifndef BUTTON_H
#define BUTTON_H

#include "UiEntity.h"

class Button :
	public UiEntity
{
private:
	/*Variables*/
	unsigned char buttonState;

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	std::stack<unsigned char> *eventsPtr;
	unsigned char signal;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:

	/*Constructors Destructors*/
	Button(float x_pos, float y_pos, float width, float height,
		sf::Font *font, std::string text,
		std::stack<unsigned char> *eventsPtr, unsigned char signal);
	virtual ~Button();

	/*Functions*/

	/*Updater Renderers*/
	void update(const sf::Vector2f& mousePosWindow);
	void render(sf::RenderTarget* target);
};

#endif // !BUTTON_H

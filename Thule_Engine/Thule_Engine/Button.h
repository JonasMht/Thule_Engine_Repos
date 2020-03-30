#ifndef BUTTON_H
#define BUTTON_H

#include "Sun.h"

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};// sets values for const values n+1 starting at 0;

class Button
{
private:
	/*Variables*/
	unsigned char buttonState;


	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:

	/*Constructors Destructors*/
	Button(float x_pos, float y_pos, float width, float height,
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	/*Accessors*/

	bool isPressed();


	/*Functions*/
	void update(const sf::Vector2f mousePosView);
	void render(sf::RenderTarget* target);
};

#endif // !BUTTON_H
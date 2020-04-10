#ifndef BUTTON_H
#define BUTTON_H

#include "UiEntity.h"

class Button :
	public UiEntity
{
private:
	/*Variables*/
	bool wasClicked;

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	float x_pos, y_pos, width, height; // all in percent %

	std::stack<unsigned char> *eventsPtr;
	unsigned char signal;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:

	/*Constructors Destructors*/
	Button(float x_pos, float y_pos, float width, float height,
		sf::Font *font, std::string text,
		std::stack<unsigned char> *eventsPtr, unsigned char signal,
		sf::RenderWindow* window);
	virtual ~Button();

	/*Functions*/
	void onWindowResize();

	/*Updater Renderers*/
	void update(const sf::Vector2f& mousePosWindow);
	void render(sf::RenderTarget* target);
};

#endif // !BUTTON_H

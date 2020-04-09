#include "Button.h"


Button::Button(float x_pos, float y_pos, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x_pos, y_pos));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f)
		);//center the text

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->shape.setFillColor(this->idleColor); //using pointers to link dynamicaly > ease of switching colors
}

Button::~Button()
{

}

/*Accessors*/

bool Button::isPressed()
{
	// check if the button is pressed
	return this->buttonState == BTN_ACTIVE;
}

/*Functions*/

void Button::update(const sf::Vector2f& mousePosWindow)
{
	//Update the booleans for hover and active

	//Set to idle
	this->buttonState = BTN_IDLE;
	sf::Color stateColor;

	stateColor = this->idleColor;

	//check if hovered
	if (this->shape.getGlobalBounds().contains(mousePosWindow))
	{
		this->buttonState = BTN_HOVER;
		stateColor = this->hoverColor;

		//check if pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
			stateColor = this->activeColor;
		}
	}

	this->shape.setFillColor(stateColor);
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);

}

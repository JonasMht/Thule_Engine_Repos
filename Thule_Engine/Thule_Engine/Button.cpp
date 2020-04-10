#include "Button.h"


Button::Button(float x_pos, float y_pos, float width, float height,
	sf::Font *font, std::string text,
	std::stack<unsigned char> *eventsPtr, unsigned char signal,
	sf::RenderWindow* window)
{
	this->wasClicked = false;

	this->window = window;

	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->width = width;
	this->height = height;

	//set relative dimension and position
	this->shape.setPosition(sf::Vector2f(this->x_pos * this->window->getSize().x, this->y_pos * this->window->getSize().y));
	this->shape.setSize(sf::Vector2f(this->width * this->window->getSize().x, this->height *this->window->getSize().y));

    this->font = *font;
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f)
		);//center the text

	this->idleColor = sf::Color(60,130,170,255);
	this->hoverColor = sf::Color(70,160,210,255);
	this->activeColor = sf::Color(50,120,150,230);
	this->shape.setFillColor(this->idleColor);

	this->eventsPtr = eventsPtr;
	this->signal = signal;

}

Button::~Button()
{
    std::cout<<"Buton endend\n";
}

void Button::onWindowResize()
{
	//set relative dimension and position
	this->shape.setPosition(sf::Vector2f(this->x_pos * this->window->getSize().x, this->y_pos * this->window->getSize().y));
	this->shape.setSize(sf::Vector2f(this->width * this->window->getSize().x, this->height * this->window->getSize().y));
}

/*Functions*/

void Button::update(const sf::Vector2f& mousePosWindow)
{
	//Update the booleans for hover and active

	//Set to idle
	sf::Color stateColor;

	stateColor = this->idleColor;

	//check if hovered
	if (this->shape.getGlobalBounds().contains(mousePosWindow))
	{
		stateColor = this->hoverColor;

		//check if pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->wasClicked = true;
			stateColor = this->activeColor;
		}
		else if (this->wasClicked)
		{
			this->wasClicked = false;
			this->eventsPtr->push(this->signal);
		}
	}
	else
	{
		this->wasClicked = false;
	}
	this->shape.setFillColor(stateColor);
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

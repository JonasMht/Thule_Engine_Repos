#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "EngineState.h"

class MainMenuState :
	public State
{
private:
	/*Variables*/
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	/*Private functions*/
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	/*Constructors Destructors*/
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();


	/*Functions*/
	void endState();

	void updateInput(const float& delta);
	void updateButtons();
	void update(const float& delta);

	void renderButtons();
	void render();
	

};

#endif // !MAINMENUSTATE_H
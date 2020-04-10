#ifndef STATE_H
#define STATE_H

#include "Sun.h"

//Manage loaded files in memory
class State
{
private:
protected:
	/*Variables*/
	sf::RenderWindow* window;
	std::map < std::string, int >* supportedKeys;
	std::map < std::string, int > keybinds; //Each state has its own keybinds
	bool quitState; // deletes the state in engine loop if true
	//bool quitApplication; // deletes the state in engine loop if true // mabe add it if needed

	UiEntity* UI;
	sf::View UiView;

	sf::Vector2i mousePosScreen; //Integer Vec2
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView; //Float Vec2

	//Resources
	std::vector<sf::Texture> textures;

public:
	/*Initialization*/
	virtual void initUiView();
	virtual void initKeybinds() = 0;

	/*Constructors Destructors*/
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	/*Functions*/
	const bool& getQuitState();// returns the quitState value

	virtual void checkForQuitState();// check if quit conditions are met

	/*Events*/
	virtual void endEntity() = 0;
	virtual void onWindowResize(); //Window resize event
	virtual void onMouseScroll(const float scrollDir, const float& delta); //mouse scroll event
	virtual void onMouseMiddleClick();
	virtual void onMouseMiddleRelease();
	virtual void onMouseLeftClick();
	virtual void onMouseLeftRelease();
	virtual void onMouseRightClick();
	virtual void onMouseRightRelease();

	/*Updaters and Renderers*/
	virtual void updateMousePositions(); // If called updates all 3 mouse pos spaces
	virtual void updateInput(const float& delta) = 0;
	virtual void update(const float& delta) = 0; //init to 0 to be sure it's a pure virtual function => means it needs to be defined in a child class.
	virtual void render() = 0;
};


#endif // !STATE_H

#ifndef ENGINE_H //linux of macos incompatibility fix
#define ENGINE_H

/*State Includes*/
#include"MainMenuState.h"


class Engine
{
private:
	/*Variables*/
	sf::RenderWindow *window;
	sf::ContextSettings settings;

	sf::Event event;

	//Count time between loops/frames
	sf::Clock deltaClock;
	float delta;

	sf::Clock runTime;


	std::stack<State*> states; //stacks can be moved and popped
	std::stack<unsigned char> engineEvents;//is passed into entitiess such as butons htat insert a number coresponding to a definded event which gets handled by the Engine entity

	std::map<std::string, int> supportedKeys;//array with keys rather than indexes

	/*Initialization*/
	void initWindow();
	void initKeys();
	void initStates();


public:
	/*Constructors Destructors*/
	Engine(); // constructor
	virtual ~Engine(); // destructor

	/*Functions*/

	//Regular
	void endApplication();

	//Updates
	void updateDelta();
	void updateEvents();
	void update();
	//Render
	void render();
	//Core
	void run(); // game loop
};

#endif // !ENGINE_H

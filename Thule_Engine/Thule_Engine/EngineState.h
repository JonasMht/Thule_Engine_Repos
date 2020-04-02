#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include "State.h"


class EngineState :
	public State
{
private:
	std::list<SpaceEntity*> entities;
	sf::View mainView;
	sf::View minimapView;
	sf::Event event;

	

	/*Private functions*/
	void initKeybinds();
	void initSystems();
	void initView();

public:

	/*Constructors Destructors*/
	EngineState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~EngineState();

	/*Functions*/
	void endState();

	void updateInput(const float& delta);
	
	void onWindowResize();
	void updateWindowDrag();
	void onMouseScroll(signed char scrollDir, const float& delta);
	void update(const float& delta);
	void render();

};

#endif // !ENGINESTATE_H
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


	float zoom, zoomTarget, initialWidth, heightWidthRatio;
	float doubleClickTimer = 0;
	sf::Clock clickClock;

	/*Private functions*/
	void initKeybinds();
	void initSystems();
	void initView();

public:

	/*Constructors Destructors*/
	EngineState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~EngineState();

	/*Functions*/
	void endState(); // called at the end of this entity

	void updateInput(const float& delta); //Update keybinds
	
	/*Called if ...*/
	void onWindowResize();
	void onDubbleClick();
	void onViewDrag();
	
	/*Mouse Events*/
	void onMouseScroll(signed char scrollDir, const float& delta);
	void onMouseMiddleClick();
	void onMouseMiddleRelease();
	void onMouseLeftClick();
	void onMouseLeftRelease();
	void onMouseRightClick();
	void onMouseRightRelease();
	
	
	/*Updaters and Renderers*/
	void updateZoom();
	void update(const float& delta);
	void render();

};

#endif // !ENGINESTATE_H
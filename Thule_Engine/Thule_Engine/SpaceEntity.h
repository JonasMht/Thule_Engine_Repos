#ifndef SOURCE_H
#define SOURCE_H


#include "Source.h"

class SpaceEntity
{
public:
	/*Variables*/
	sf::Vector2f pos;
	bool life;

	/*Constructor Destructor*/
	SpaceEntity();
	virtual ~SpaceEntity();

	/*Functions*/
	virtual void update(const float& delta){};
	virtual void render(sf::RenderTarget* target = NULL){};
};

#endif // !SOURCE_H

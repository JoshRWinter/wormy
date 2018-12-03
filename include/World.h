#ifndef WORLD_H
#define WORLD_H

#include <wormy.h>
#include <vector>

class World
{
public:
	World();

	void reset();
	void step();
	void render(Renderer&) const;

private:
	struct
	{
		std::vector<Food> food;
	} entities;
};

#endif WORLD_H

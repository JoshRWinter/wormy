#ifndef WORLD_H
#define WORLD_H

#include <wormy.h>
#include <vector>

struct World
{
	World();

	void reset();
	void step();
	void render(Renderer&) const;

	struct
	{
		float left, right, bottom, top;
	} screen;

	struct
	{
		Worm player;
		std::vector<Worm> worms;
		std::vector<Food> food;
	} entity;

	Entity background;

	float mousex, mousey;
};

#endif WORLD_H

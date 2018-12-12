#ifndef WORLD_H
#define WORLD_H

#include <wormy.h>
#include <vector>

struct World
{
	World(win::display&, win::roll&);

	void reset();
	void step();
	void render();

	Renderer renderer;

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

	float mousex_raw, mousey_raw;
	float mousex, mousey;
};

#endif WORLD_H

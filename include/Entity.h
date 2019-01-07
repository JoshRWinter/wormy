#ifndef ENTITY_H
#define ENTITY_H

#include <deque>

class Renderer;
class World;

struct Entity
{
	bool collide(const Entity&) const;

	float x, y, s;
	win::color color;
};

struct Worm
{
	struct Link : Entity
	{
		struct Position { float x, y; };
		static constexpr int WAIT = 10;

		Link(float, float, const win::color&);
		Link(const Worm&);

		static constexpr float LINK_SIZE = 0.4f;

		float xv, yv;
		int wait;

		std::deque<Position> history;
	};

	Worm();
	Worm(float, float, const win::color&);

	void step(World&);
	void render_geometry(Renderer&) const;
	void render_light(Renderer&) const;

	static void step(std::vector<Worm>&, World&);
	static void render_light(Renderer&, const std::vector<Worm>&);
	static void render_geometry(Renderer&, const std::vector<Worm>&);

	std::vector<Link> links;
	win::color color;
};

struct Food : Entity
{
	static constexpr float WIDTH = 0.3f;
	static constexpr float VARIANCE = 0.1f;

	Food(float, float);

	static void step(std::vector<Food>&);
	static void render(Renderer&, const std::vector<Food>&);
	static void create(std::vector<Food>&);
};

#endif

#ifndef ENTITY_H
#define ENTITY_H

class Renderer;
class World;

struct Entity
{
	bool collide(const Entity&) const;

	float x, y, s;
	int r, g, b;
};

struct Worm
{
	struct Link : Entity
	{
		static constexpr float LINK_SIZE = 0.4f;

		float xv, yv;
	};

	Worm();
	Worm(float, float, int, int, int);

	void step(World&);
	void render(Renderer&) const;

	static void step(std::vector<Worm>&, World&);
	static void render(Renderer&, const std::vector<Worm>&);

	std::vector<Link> links;
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

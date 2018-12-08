#ifndef ENTITY_H
#define ENTITY_H

class Renderer;

struct Entity
{
	bool collide(const Entity&) const;

	float x, y, s;
	int r, g, b;
};

struct Link : Entity
{
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

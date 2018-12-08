#ifndef ENTITY_H
#define ENTITY_H

struct Entity
{
	bool collide(const Entity&) const;

	float x, y, s;
};

struct Link : Entity
{
};

struct Food : Entity
{
	static constexpr float WIDTH = 1.0f;
	static constexpr float VARIANCE = 0.2f;

	Food(float, float);

	static void step(std::vector<Food>&);
	static void render(Renderer&, const std::vector<Food>&);
	static void create(std::vector<Food>&);

	int r, g, b;
};

#endif

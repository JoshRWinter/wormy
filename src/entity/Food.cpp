#include <wormy.h>

Food::Food(float xpos, float ypos)
{
	x = xpos;
	y = ypos;

	s = WIDTH;// +random(-VARIANCE, VARIANCE);
	r = random(0, 255);
	g = random(0, 255);
	b = random(0, 255);
}

void Food::step(std::vector<Food> &food_list)
{
	for (auto &food = food_list.begin(); food != food_list.end();)
	{
		++food;
	}
}

void Food::render(Renderer &renderer, const std::vector<Food> &food_list)
{
	for (const auto &food : food_list)
	{
		renderer.add(food.x, food.y, food.r, food.g, food.b);
	}
}

void Food::create(std::vector<Food> &food_list)
{
	const int count = random(10, 15);

	for (int i = 0; i < count; ++i)
	{
		food_list.emplace_back(random(-10.0f, 10.0f), random(-10.0f, 10.0f));
	}
}
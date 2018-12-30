#include <wormy.h>

Food::Food(float xpos, float ypos)
{
	x = xpos;
	y = ypos;

	s = WIDTH + mersenne(-VARIANCE, VARIANCE);
	color.red = mersenne(0.2f, 0.8f);
	color.green = mersenne(0.2f, 0.8f);
	color.blue = mersenne(0.2f, 0.8f);
}

void Food::step(std::vector<Food> &food_list)
{
	for (auto food = food_list.begin(); food != food_list.end();)
	{
		++food;
	}
}

void Food::render(Renderer &renderer, const std::vector<Food> &food_list)
{
	for (const auto &food : food_list)
	{
		renderer.add(food);
	}
}

void Food::create(std::vector<Food> &food_list)
{
	const int count = mersenne(60, 95);

	for (int i = 0; i < count; ++i)
	{
		food_list.emplace_back(mersenne(-10.0f, 10.0f), mersenne(-10.0f, 10.0f));
	}
}

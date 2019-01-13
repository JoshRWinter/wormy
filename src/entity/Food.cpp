#include <wormy.h>

Food::Food(float xpos, float ypos)
{
	x = xpos;
	y = ypos;

	s = mersenne(SIZE_LOW, SIZE_HIGH);
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

void Food::render_geometry(Renderer &renderer, const std::vector<Food> &food_list)
{
	for (const auto &food : food_list)
	{
		Entity e;
		e.x = food.x;
		e.y = food.y;
		e.s = food.s;
		e.color = win::color(1.0f, 1.0f, 1.0f, 1.0f);

		renderer.add(e);
	}
}

void Food::render_light(Renderer &renderer, const std::vector<Food> &food_list)
{
	for (const auto &food : food_list)
	{
		Entity e;
		e.x = food.x + (food.s / 2.0f);
		e.y = food.y + (food.s / 2.0f);
		e.s = food.s * 6.0f;
		e.color = food.color;

		renderer.add_light(e);
	}
}

void Food::create(std::vector<Food> &food_list)
{
	const int count = 300;

	for (int i = 0; i < count; ++i)
	{
		food_list.emplace_back(mersenne(-10.0f, 10.0f), mersenne(-10.0f, 10.0f));
	}
}

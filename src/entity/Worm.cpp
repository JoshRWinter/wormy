#include <cmath>

#include <wormy.h>

Worm::Worm()
	: Worm(0.0f, 0.0f, 255, 70, 30)
{
}

Worm::Worm(float xpos, float ypos, int r, int g, int b)
{
	Link l;
	l.x = xpos;
	l.y = ypos;
	l.s = Link::LINK_SIZE;

	l.xv = 0.0f;
	l.yv = 0.0f;

	l.r = r;
	l.g = g;
	l.b = b;

	links.push_back(l);
}

void Worm::step(World &world)
{
	const bool player = &world.entity.player == this;

	for(Link &link : links)
	{
		const bool head = &link == &links[0]; // this link is the head link

		if(player)
		{
			// have the first link follow the mouse
			if(head)
			{
				const float angle = std::atan2f((link.y + (Link::LINK_SIZE / 2.0f)) - world.mousey, (link.x + (Link::LINK_SIZE / 2.0f)) - world.mousex);

				const float speed = 0.01f;
				link.xv = -cosf(angle) * speed;
				link.yv = -sin(angle) * speed;
			}
		}

		link.x += link.xv;
		link.y += link.yv;

		// check for collisions with food pellets
		if(head)
		for(auto pellet = world.entity.food.begin(); pellet != world.entity.food.end();)
		{
			if(link.collide(*pellet))
			{
				pellet = world.entity.food.erase(pellet);
				continue;
			}

			++pellet;
		}
	}
}

void Worm::render(Renderer &renderer) const
{
	for (const Link &link : links)
		renderer.add(link);
}

void Worm::step(std::vector<Worm> &worm_list, World &world)
{
	for(Worm &worm : worm_list)
		worm.step(world);
}

void Worm::render(Renderer &renderer, const std::vector<Worm> &worm_list)
{
	for(const Worm &worm : worm_list)
	{
		worm.render(renderer);
	}
}

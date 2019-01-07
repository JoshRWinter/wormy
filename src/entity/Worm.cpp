#include <cmath>

#include <wormy.h>

// called for creating head link
Worm::Link::Link(float xpos, float ypos, const win::color &color_)
{
	x = xpos;
	y = ypos;
	s = LINK_SIZE;
	wait = WAIT;

	color = color_;

	xv = 0.0f;
	yv = 0.0f;
}

// adding child links
Worm::Link::Link(const Worm &parent)
{
	const Link &tail = parent.links[parent.links.size() - 1];

	x = tail.x;
	y = tail.y;
	s = LINK_SIZE;
	wait = WAIT;

	color = tail.color;

	xv = 0.0f;
	yv = 0.0f;
}

// for the player worm
Worm::Worm()
	: color(1.0f, 1.0f, 0.0f)
{
	const Link fake(0.0f, 0.0f, color);
	links.push_back(fake);
}

Worm::Worm(const float xpos, const float ypos, const win::color &color_)
{
	color = color_;

	links.push_back({xpos, ypos, color});
}

void Worm::step(World &world)
{
	const bool player = &world.entity.player == this;

	for(int i = 0; i < links.size(); ++i)
	{

		const bool head = i == 0; // this link is the head link

		Link &l = links[i];
		// check for collisions with food pellets
		if(head)
		{
			for(auto pellet = world.entity.food.begin(); pellet != world.entity.food.end();)
			{
				if(l.collide(*pellet))
				{
					pellet = world.entity.food.erase(pellet);
					links.push_back({*this});
					break;
				}

				++pellet;
			}
		}

		Link &link = links[i];
		const bool tail = i == (int)links.size() - 1;

		if(player)
		{
			// have the first link follow the mouse
			if(head)
			{
				const float angle = std::atan2f((link.y + (Link::LINK_SIZE / 2.0f)) - world.mousey, (link.x + (Link::LINK_SIZE / 2.0f)) - world.mousex);

				const float speed = 0.02f;
				link.xv = -cosf(angle) * speed;
				link.yv = -sin(angle) * speed;
			}
		}

		if(!tail)
		{
			// tell next link where this one was
			Link &next = links[i + 1];
			Link::Position pos;
			pos.x = link.x;
			pos.y = link.y;

			next.history.push_front(pos);
		}

		if(!head)
		{
			const Link &prev = links[i - 1];

			if(link.wait > 0)
				--link.wait;
			if(!link.wait)
			{
				// follow previous link
				Link::Position pos = link.history.back();
				link.history.pop_back();
				link.x = pos.x;
				link.y = pos.y;
			}
		}
		else
		{
			link.x += link.xv;
			link.y += link.yv;
		}
	}
}

void Worm::step(std::vector<Worm> &worm_list, World &world)
{
	for(Worm &worm : worm_list)
		worm.step(world);
}

void Worm::render_geometry(Renderer &renderer) const
{
	for (const Link &link : links)
		renderer.add(link);
}

void Worm::render_light(Renderer &renderer) const
{
	for(const Link &link : links)
		renderer.add_light(link);
}

void Worm::render_geometry(Renderer &renderer, const std::vector<Worm> &worm_list)
{
	for(const Worm &worm : worm_list)
	{
		worm.render_geometry(renderer);
	}
}

void Worm::render_light(Renderer &renderer, const std::vector<Worm> &worm_list)
{
	for(const Worm &worm : worm_list)
	{
		worm.render_light(renderer);
	}
}

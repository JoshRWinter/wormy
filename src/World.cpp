#include <wormy.h>

World::World()
{
	screen.left = -8.0f;
	screen.right = 8.0f;
	screen.bottom = 4.5f;
	screen.top = -4.5f;
}

void World::reset()
{
}

void World::step()
{
	if (entity.food.size() == 0)
		Food::create(entity.food);

	// process player and other worms
	entity.player.step(*this);
	Worm::step(entity.worms, *this);

	// process food pellets
	Food::step(entity.food);
}

void World::render(Renderer &renderer) const
{
	glClear(GL_COLOR_BUFFER_BIT);

	renderer.font.renderer.draw(renderer.font.main, "wormy", 0.0f, -4.0f, win::color(255, 255, 255), win::font_renderer::CENTERED);

	glBindVertexArray(renderer.vao);
	glUseProgram(renderer.program);

	glBindTexture(GL_TEXTURE_2D, renderer.tpack[0]);
	Food::render(renderer, entity.food);
	entity.player.render(renderer);
	Worm::render(renderer, entity.worms);

	renderer.send();
}

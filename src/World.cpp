#include <wormy.h>

World::World()
{
}

void World::reset()
{
}

void World::step()
{
	if (entity.food.size() == 0)
		Food::create(entity.food);

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

	renderer.send();
}

#include <wormy.h>

static const float common_texcoords[] =
{
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f
};

static const float background_texcoords[] =
{
	-40.0f, 40.0f,
	-40.0f, -40.0f,
	40.0f, -40.0f,
	40.0f, 40.0f
};

World::World()
{
	screen.left = -8.0f;
	screen.right = 8.0f;
	screen.bottom = 4.5f;
	screen.top = -4.5f;

	background.x = -40.0f;
	background.y = background.x;
	background.s = 80.0f;
	background.color.red = 1.0f;
	background.color.green = 1.0f;
	background.color.blue = 1.0f;
	background.color.alpha = 1.0f;
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
	glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo.triangle_texcoord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 8, sizeof(float) * 8, background_texcoords);
	glBindTexture(GL_TEXTURE_2D, renderer.tpack[1]);
	renderer.add(background);
	renderer.send();

	renderer.font.renderer.draw(renderer.font.main, "wormy", 0.0f, -4.0f, win::color(255, 255, 255), win::font_renderer::CENTERED);

	glBindVertexArray(renderer.vao);
	glUseProgram(renderer.program);

	glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo.triangle_texcoord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 8, sizeof(float) * 8, common_texcoords);
	glBindTexture(GL_TEXTURE_2D, renderer.tpack[0]);
	Food::render(renderer, entity.food);
	entity.player.render(renderer);
	Worm::render(renderer, entity.worms);

	renderer.send();
}

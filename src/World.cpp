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

World::World(win::display &display, win::roll &roll)
	: renderer(display, roll)
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

	mousex = 0;
	mousey = 0;
	mousex_raw = 0;
	mousey_raw = 0;
}

void World::reset()
{
}

void World::step()
{
	// configure mouse
	mousex = (((float)mousex_raw / renderer.window_width) * (screen.right * 2.0f) - screen.right) + entity.player.links[0].x;
	mousey = (((float)mousey_raw / renderer.window_height) * (screen.bottom * 2.0f) - screen.bottom) + entity.player.links[0].y;
	if (entity.food.size() == 0)
		Food::create(entity.food);

	// process player and other worms
	entity.player.step(*this);
	Worm::step(entity.worms, *this);

	// process food pellets
	Food::step(entity.food);
}

void World::render()
{
	// draw backdrop
	renderer.player_x = entity.player.links[0].x;
	renderer.player_y = entity.player.links[0].y;
	glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo.geometry.triangle_texcoord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 8, sizeof(float) * 8, background_texcoords);
	glBindTexture(GL_TEXTURE_2D, renderer.tpack[1]);
	renderer.add(background);
	renderer.send();

	// wormy header
	renderer.font.renderer.draw(renderer.font.main, "wormy", 0.0f, -4.0f, win::color(255, 255, 255), win::font_renderer::CENTERED);

	// draw lights
	glBindVertexArray(renderer.vao.light);
	glUseProgram(renderer.program.light);

	Food::render_light(renderer, entity.food);

	renderer.send_light();

	// draw worms and food pellets
	glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo.geometry.triangle_texcoord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 8, sizeof(float) * 8, common_texcoords);
	glBindTexture(GL_TEXTURE_2D, renderer.tpack[0]);
	Food::render_geometry(renderer, entity.food);
	entity.player.render_geometry(renderer);
	Worm::render_geometry(renderer, entity.worms);

	renderer.send();
}

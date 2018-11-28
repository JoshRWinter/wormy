#include <wormy.h>

Renderer::Renderer(win::display &display, win::roll &roll)
{
	win::load_extensions();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	font.renderer = display.make_font_renderer(display.width(), display.height(), -8.0f, 8.0f, 4.5f, -4.5f);
	font.main = font.renderer.make_font(roll["SF-Hollywood-Hills.ttf"], 1.0f);
}

Renderer::~Renderer()
{
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	font.renderer.draw(font.main, "wormy", 0.0f, -4.0f, win::color(1.0f, 1.0f, 1.0f, 1.0f), win::font_renderer::CENTERED);
}

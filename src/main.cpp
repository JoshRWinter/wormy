#include <exception>

#include <wormy.h>

static void go();
static void render(Renderer&);

int main()
{
	try
	{
		go();
	}
	catch(const std::exception &e)
	{
		win::bug(e.what());
		return 1;
	}

	return 0;
}

void go()
{
	win::system system;
	bool quit = false;

	win::display display = system.make_display("WORMY", 1280, 720);
	display.vsync(true);

	win::roll roll("assets");
	World world;
	Renderer renderer(display, roll);

	// button handler
	display.event_button([&quit](win::button button, bool)
	{
		if(button == win::button::ESC)
			quit = true;
	});

	// mouse handler
	const int window_width = display.width();
	const int window_height = display.height();
	display.event_mouse([&quit, &world, window_width, window_height](int x, int y)
	{
		world.mousex = ((float)x / window_width) * (world.screen.right * 2.0f) - world.screen.right;
		world.mousey = ((float)y / window_height) * (world.screen.bottom * 2.0f) - world.screen.bottom;
	});

	while(display.process() && !quit)
	{
		world.step();
		world.render(renderer);

		display.swap();
	}
}

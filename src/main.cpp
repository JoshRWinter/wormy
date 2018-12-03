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

	// button handler
	display.event_button([&quit](win::button button, bool)
	{
		if(button == win::button::ESC)
			quit = true;
	});

	win::roll roll("assets");
	World world;
	Renderer renderer(display, roll);

	while(display.process() && !quit)
	{
		world.step();
		world.render(renderer);

		display.swap();
	}
}

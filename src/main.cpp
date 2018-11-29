#include <exception>

#include <wormy.h>

static void go();

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
	Renderer renderer(display, roll);

	while(display.process() && !quit)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		renderer.add(0.0f, 0.0f, 255, 255, 0);
		renderer.send();

		display.swap();
	}
}

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	Renderer(win::display &display, win::roll&);
	~Renderer();

	void draw();

private:
	struct
	{
		win::font_renderer renderer;
		win::font main;
	} font;
};

#endif

#ifndef RENDERER_H
#define RENDERER_H

struct Renderer
{
	Renderer(win::display &display, win::roll&);
	~Renderer();

	void add(const Entity&);
	void send();

	struct
	{
		win::font_renderer renderer;
		win::font main;
	} font;

	struct
	{
		unsigned index;
		unsigned triangle_texcoord;
		unsigned position_size;
		unsigned color;
	} vbo;

	struct
	{
		std::vector<float> position_size;
		std::vector<unsigned char> color;
	} buffer;

	unsigned vao;
	unsigned program;
	float player_x, player_y;
	int window_width, window_height;

	win::tpack tpack;
};

#endif

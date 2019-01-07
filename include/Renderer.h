#ifndef RENDERER_H
#define RENDERER_H

struct Renderer
{
	Renderer(win::display &display, win::roll&);
	~Renderer();

	void add(const Entity&);
	void add_light(const Entity&);
	void send();

	struct
	{
		win::font_renderer renderer;
		win::font main;
	} font;

	struct
	{
		struct
		{
			unsigned index;
			unsigned triangle_texcoord;
			unsigned position_size;
			unsigned color;
		} geometry;

		struct
		{
			unsigned index;
			unsigned triangle;
			unsigned position_size;
			unsigned color;
		} light;
	} vbo;

	struct
	{
		struct
		{
			std::vector<float> position_size;
			std::vector<unsigned char> color;
		} geometry;

		struct
		{
			std::vector<float> position_size;
			std::vector<unsigned char> color;
		} light;
	} buffer;

	struct
	{
		unsigned geometry;
		unsigned light;
	} vao;

	struct
	{
		unsigned geometry;
		unsigned light;
	} program;

	float player_x, player_y;
	int window_width, window_height;

	win::tpack tpack;
};

#endif

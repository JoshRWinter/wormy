#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	Renderer(win::display &display, win::roll&);
	~Renderer();

	void add(float, float, unsigned char, unsigned char, unsigned char);
	void send();

private:
	struct
	{
		win::font_renderer renderer;
		win::font main;
	} font;

	struct
	{
		unsigned index;
		unsigned vertex;
		unsigned position;
		unsigned color;
	} vbo;

	struct
	{
		std::vector<float> vertex;
		std::vector<unsigned char> color;
	} buffer;

	unsigned vao;
	unsigned program;

};

#endif

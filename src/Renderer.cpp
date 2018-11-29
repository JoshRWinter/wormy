#include <wormy.h>

Renderer::Renderer(win::display &display, win::roll &roll)
{
	win::load_extensions();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	font.renderer = display.make_font_renderer(display.width(), display.height(), -8.0f, 8.0f, 4.5f, -4.5f);
	font.main = font.renderer.make_font(roll["SF-Hollywood-Hills.ttf"], 1.0f);

	tpack = win::tpack(roll.select({ "dot.tga" }));

	// shaders
	program = win::load_shaders(roll["common.vert"], roll["common.frag"]);
	glUseProgram(program);

	float matrix[16];
	win::init_ortho(matrix, -8.0f, 8.0f, 4.5f, -4.5f);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, matrix);

	const float verts[] =
	{
		-0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, 0.5f,	0.0f, 0.0f,
		0.5f, 0.5f,		1.0f, 0.0f,
		0.5f, -0.5f,	1.0f, 1.0f
	};

	const unsigned indices[] =
	{
		0, 1, 2, 0, 2, 3
	};

	// vertex array
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// element buffer
	glGenBuffers(1, &vbo.index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// vertex buffer
	glGenBuffers(1, &vbo.vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 4, NULL);
	glVertexAttribPointer(3, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(3);

	// position buffer
	glGenBuffers(1, &vbo.position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.position);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(1);

	// color buffer
	glGenBuffers(1, &vbo.color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.color);
	glVertexAttribPointer(2, 3, GL_UNSIGNED_BYTE, true, 0, NULL);
	glVertexAttribDivisor(2, 1);
	glEnableVertexAttribArray(2);
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &vbo.index);
	glDeleteBuffers(1, &vbo.vertex);
	glDeleteBuffers(1, &vbo.position);
	glDeleteBuffers(1, &vbo.color);

	glDeleteVertexArrays(1, &vao);

	glDeleteProgram(program);
}

void Renderer::add(float x, float y, unsigned char r, unsigned char g, unsigned char b)
{
	buffer.vertex.push_back(x);
	buffer.vertex.push_back(y);

	buffer.color.push_back(r);
	buffer.color.push_back(g);
	buffer.color.push_back(b);
}

void Renderer::send()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo.position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.vertex.size(), buffer.vertex.data(), GL_DYNAMIC_DRAW);
	buffer.vertex.clear();

	glBindBuffer(GL_ARRAY_BUFFER, vbo.color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * buffer.color.size(), buffer.color.data(), GL_DYNAMIC_DRAW);
	buffer.color.clear();

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, 1);
}

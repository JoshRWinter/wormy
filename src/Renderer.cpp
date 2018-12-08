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

	// triangle data and texcoords buffer
	glGenBuffers(1, &vbo.triangle_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.triangle_texcoord);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 4, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// position and size buffer
	glGenBuffers(1, &vbo.position_size);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.position_size);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 3, NULL);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(float) * 3, (void*)(sizeof(float) * 2));
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	// color buffer
	glGenBuffers(1, &vbo.color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.color);
	glVertexAttribPointer(4, 3, GL_UNSIGNED_BYTE, true, 0, NULL);
	glVertexAttribDivisor(4, 1);
	glEnableVertexAttribArray(4);
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &vbo.index);
	glDeleteBuffers(1, &vbo.triangle_texcoord);
	glDeleteBuffers(1, &vbo.position_size);
	glDeleteBuffers(1, &vbo.color);

	glDeleteVertexArrays(1, &vao);

	glDeleteProgram(program);
}

void Renderer::add(const Entity &entity)
{
	buffer.position_size.push_back(entity.x);
	buffer.position_size.push_back(entity.y);
	buffer.position_size.push_back(entity.s);

	buffer.color.push_back(entity.r);
	buffer.color.push_back(entity.g);
	buffer.color.push_back(entity.b);
}

void Renderer::send()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo.position_size);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.position_size.size(), buffer.position_size.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * buffer.color.size(), buffer.color.data(), GL_DYNAMIC_DRAW);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, buffer.position_size.size() / 3);

	buffer.position_size.clear();
	buffer.color.clear();
}

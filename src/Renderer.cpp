#include <wormy.h>

Renderer::Renderer(win::display &display, win::roll &roll)
{
	window_width = display.width();
	window_height = display.height();

	win::load_extensions();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	font.renderer = display.make_font_renderer(display.width(), display.height(), -8.0f, 8.0f, 4.5f, -4.5f);
	font.main = font.renderer.make_font(roll["SF-Hollywood-Hills.ttf"], 1.0f);

	tpack = win::tpack(roll.select({"dot.tga", "background.tga"}));

	glBindTexture(GL_TEXTURE_2D, tpack[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// shaders
	program.geometry = win::load_shaders(roll["common.vert"], roll["common.frag"]);
	program.light = win::load_shaders(roll["light.vert"], roll["light.frag"]);

	// uniforms
	float matrix[16];
	win::init_ortho(matrix, -8.0f, 8.0f, 4.5f, -4.5f);

	glUseProgram(program.geometry);
	glUniformMatrix4fv(glGetUniformLocation(program.geometry, "projection"), 1, false, matrix);

	glUseProgram(program.light);
	glUniformMatrix4fv(glGetUniformLocation(program.light, "projection"), 1, false, matrix);
	glUniform2i(glGetUniformLocation(program.light, "framebuffer_dims"), display.width(), display.height());
	glUniform2f(glGetUniformLocation(program.light, "world_dims"), 16.0f, 9.0f);

	const float geom_verts[] =
	{
		// triangle
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f,

		// initial texcoords
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	const unsigned indices[] =
	{
		0, 1, 2, 0, 2, 3
	};

	/* GEOMETRY */

	// vertex array
	glGenVertexArrays(1, &vao.geometry);
	glBindVertexArray(vao.geometry);

	// element buffer
	glGenBuffers(1, &vbo.geometry.index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.geometry.index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// triangle data
	glGenBuffers(1, &vbo.geometry.triangle_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.geometry.triangle_texcoord);
	glBufferData(GL_ARRAY_BUFFER, sizeof(geom_verts), geom_verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// position and size buffer
	glGenBuffers(1, &vbo.geometry.position_size);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.geometry.position_size);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 3, NULL);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(float) * 3, (void*)(sizeof(float) * 2));
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	// color buffer
	glGenBuffers(1, &vbo.geometry.color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.geometry.color);
	glVertexAttribPointer(4, 3, GL_UNSIGNED_BYTE, true, 0, NULL);
	glVertexAttribDivisor(4, 1);
	glEnableVertexAttribArray(4);

	/* LIGHTS */

	const float light_verts[] =
	{
		// triangle
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f,
	};

	glGenVertexArrays(1, &vao.light);
	glBindVertexArray(vao.light);

	// element buffer
	glGenBuffers(1, &vbo.light.index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.light.index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// triangle buffer
	glGenBuffers(1, &vbo.light.triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.light.triangle);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glBufferData(GL_ARRAY_BUFFER, sizeof(light_verts), light_verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	// positon and size buffers
	glGenBuffers(1, &vbo.light.position_size);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.light.position_size);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 3, NULL); // position
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(float) * 3, (void*)(sizeof(float) * 2)); // size
	glVertexAttribDivisor(2, 1);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// color buffer
	glGenBuffers(1, &vbo.light.color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.light.color);
	glVertexAttribPointer(3, 3, GL_UNSIGNED_BYTE, true, 0, NULL);
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(3);
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &vbo.geometry.index);
	glDeleteBuffers(1, &vbo.geometry.triangle_texcoord);
	glDeleteBuffers(1, &vbo.geometry.position_size);
	glDeleteBuffers(1, &vbo.geometry.color);

	glDeleteBuffers(1, &vbo.light.index);
	glDeleteBuffers(1, &vbo.light.triangle);
	glDeleteBuffers(1, &vbo.light.position_size);
	glDeleteBuffers(1, &vbo.light.color);

	glDeleteVertexArrays(1, &vao.geometry);
	glDeleteVertexArrays(1, &vao.light);

	glDeleteProgram(program.geometry);
}

void Renderer::add(const Entity &entity)
{
	buffer.geometry.position_size.push_back(entity.x - player_x);
	buffer.geometry.position_size.push_back(entity.y - player_y);
	buffer.geometry.position_size.push_back(entity.s);

	buffer.geometry.color.push_back(entity.color.red * 255);
	buffer.geometry.color.push_back(entity.color.green * 255);
	buffer.geometry.color.push_back(entity.color.blue * 255);
}

void Renderer::add_light(const Entity &entity)
{
	buffer.light.position_size.push_back(entity.x - player_x);
	buffer.light.position_size.push_back(entity.y - player_y);
	buffer.light.position_size.push_back(entity.s);

	buffer.light.color.push_back(entity.color.red * 255);
	buffer.light.color.push_back(entity.color.green * 255);
	buffer.light.color.push_back(entity.color.blue * 255);
}

void Renderer::send()
{
	glBindVertexArray(vao.geometry);
	glUseProgram(program.geometry);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.geometry.position_size);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.geometry.position_size.size(), buffer.geometry.position_size.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.geometry.color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * buffer.geometry.color.size(), buffer.geometry.color.data(), GL_DYNAMIC_DRAW);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, buffer.geometry.position_size.size() / 3);

	buffer.geometry.position_size.clear();
	buffer.geometry.color.clear();
}

void Renderer::send_light()
{
	glBindVertexArray(vao.light);
	glUseProgram(program.light);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.light.position_size);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.light.position_size.size(), buffer.light.position_size.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.light.color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * buffer.light.color.size(), buffer.light.color.data(), GL_DYNAMIC_DRAW);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, buffer.light.position_size.size() / 3);

	buffer.light.position_size.clear();
	buffer.light.color.clear();
}

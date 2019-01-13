#version 330 core

layout (location = 0) in vec2 triangle;
layout (location = 1) in vec2 position;
layout (location = 2) in float size;
layout (location = 3) in vec4 color;

out float fsize;
out vec4 fcolor;
out vec2 forigin;

uniform mat4 projection;

void main()
{
	fsize = size;
	fcolor = color;
	forigin = position; //vec2(position.x - (size / 2.0), position.y - (size / 2.0));

	mat4 translate = mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, position.x, position.y, 0.0, 1.0);

	gl_Position = projection * translate * vec4(triangle.x * size, triangle.y * size, 0.0f, 1.0);
}
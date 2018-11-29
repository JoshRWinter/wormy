#version 330 core

uniform mat4 projection;

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 position;
layout (location = 2) in vec3 color;

out vec3 fcolor;

void main()
{
	mat4 model = mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, position.x + 0.5, position.y + 0.5, 0.0, 1.0);
	gl_Position = projection * model * vec4(vertex.x, vertex.y, 0.0, 1.0);

	fcolor = color;
}

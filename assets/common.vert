#version 330 core

uniform mat4 projection;
const float size = 0.4;

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 position;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texcoord;

out vec3 fcolor;
out vec2 ftexcoord;

void main()
{
	mat4 model = mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, position.x + (size / 2.0), position.y + (size / 2.0), 0.0, 1.0);
	gl_Position = projection * model * vec4(vertex.x * size, vertex.y * size, 0.0, 1.0);

	fcolor = color;
	ftexcoord = texcoord;
}

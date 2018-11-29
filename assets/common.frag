#version 330 core

out vec4 color;
in vec3 fcolor;

void main()
{
	color = vec4(fcolor.rgb, 1.0);
}
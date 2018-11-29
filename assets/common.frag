#version 330 core

out vec4 color;
uniform sampler2D tex;

in vec3 fcolor;
in vec2 ftexcoord;

void main()
{
	color = texture(tex, ftexcoord) * vec4(fcolor.rgb, 1.0f);
}
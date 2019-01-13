#version 330 core

in float fsize;
in vec4 fcolor;
in vec2 forigin;
layout (origin_upper_left) in vec4 gl_FragCoord;

out vec4 color;

uniform ivec2 framebuffer_dims;
uniform vec2 world_dims;

void main()
{
	vec2 current = vec2(((gl_FragCoord.x / framebuffer_dims.x) * world_dims.x) - (world_dims.x / 2.0), ((gl_FragCoord.y / framebuffer_dims.y) * world_dims.y) - (world_dims.y / 2.0));
	float dist = distance(current, forigin) / (fsize / 2.0);
	float alpha = 1.0 - dist;
	alpha = clamp(alpha, 0.0, 1.0);

	color = vec4(fcolor.rgb, alpha);
}

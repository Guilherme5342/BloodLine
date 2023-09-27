#version 400 core

layout(location = 0) in  vec3 position;
layout(location = 1) in  vec4 colour;
layout(location = 2) in  vec2 texCoord;

out Vertex	{
	vec2 texCoord;
	vec4 colour;
} OUT;

void main(void)	{
	gl_Position		= vec4(position, 1.0);
	
	OUT.texCoord	= texCoord;
	OUT.colour		= colour;
}
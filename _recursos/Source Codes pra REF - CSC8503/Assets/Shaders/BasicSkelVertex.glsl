#version 400 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;

layout(location = 6)  in vec4 weightIndices;
layout(location = 7) in vec4 weightValues;

uniform mat4 transforms[10];
 
out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT;

void main(void)
{
	mat4 mvp 		= (projMatrix * viewMatrix * modelMatrix);
	
	vec4 skelPos = vec4(0,0,0,0);
	
	for(int i = 0; i < 4; ++i) {
		int index 		= int(weightIndices[i]);
		float weight 	= weightValues[i];

		skelPos +=  (transforms[index] * vec4(position, 1)) * weight;
	}
	skelPos.w = 1.0f;
	
	gl_Position		= mvp * skelPos;

	OUT.texCoord	= texCoord;
	OUT.colour		= colour;
}
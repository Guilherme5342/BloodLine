#version 400 core

uniform sampler2D 	mainTex;

in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN;

out vec4 fragColor;

void main(void)
{	
	if(textureSize(mainTex, 1).x < 1.0f) {
		fragColor = IN.colour;
	}
	else {
		fragColor = texture(mainTex, IN.texCoord) * IN.colour;
	}
}
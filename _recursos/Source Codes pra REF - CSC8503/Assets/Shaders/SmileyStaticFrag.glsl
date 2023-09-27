#version 400 core

uniform sampler2D 	mainTex;
uniform sampler2D   secondTex;

uniform float time; 

in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN;

out vec4 fragColor;

void main(void)	{
	vec4 smileyColour = texture(mainTex, IN.texCoord);

	if(smileyColour.b > 0.1) {
		vec2 tempTex = IN.texCoord;
		tempTex.y 	+= time;

		fragColor = texture(secondTex, tempTex);
	}
	else {
		fragColor = smileyColour;
	}
}
#version 150 core

uniform sampler2D basicTexture;

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

//In the tutorial notes, I've used gl_FragColor for the output variable. This is fine on the uni machines, but 
//doesn't play very nicely with some intel and amd graphics drivers, due to the gl_ prefix. For this reason,
//it's better to use a different variable name - so pick something sensible.
out vec4 fragColour;

void main(void)	{	
	fragColour = IN.colour * texture(basicTexture, IN.texCoord);
}
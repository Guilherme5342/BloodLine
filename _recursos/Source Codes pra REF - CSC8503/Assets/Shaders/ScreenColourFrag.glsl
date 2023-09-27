#version 400 core
uniform sampler2D 	tex; 

in Vertex	{
	smooth	vec4 	colour;
	smooth	vec2 	texCoord;
} IN;

out vec4 fragColor;

void main(void)	{
	vec3 fragPos = gl_FragCoord.rgb * 0.1;

	float r = sin(fragPos.x) * 0.5 + 0.5;
	float g = sin(fragPos.y) * 0.5 + 0.5;
	float b = sin(fragPos.z) * 0.5 + 0.5;

	fragColor.xyz  = vec3(r,g,b);	
	fragColor.a 	= 1.0;
}
#version 400 core
layout(vertices =4) out;	//num vertices in output patch
 
in Vertex	{
	vec2 texCoord;	//From Vertex Shader
} IN[];				//Equal to size of the draw call vertex count

out Vertex	{
	vec2 texCoord;	//To Evaluation Shader
} OUT[];				//Equal to the size of the layout vertex count

void main()	{
	gl_TessLevelInner[0] = 32;
	gl_TessLevelInner[1] = 32;
	gl_TessLevelOuter[0] = 32;
	gl_TessLevelOuter[1] = 32;
	gl_TessLevelOuter[2] = 32;
	gl_TessLevelOuter[3] = 32;

	OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;

	gl_out[gl_InvocationID].gl_Position = 
			gl_in[gl_InvocationID].gl_Position;
}
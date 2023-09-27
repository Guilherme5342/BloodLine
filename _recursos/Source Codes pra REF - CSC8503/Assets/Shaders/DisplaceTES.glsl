#version 400

layout(quads, cw) in;

uniform sampler2D heightMap;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

in Vertex	{ 	//Sent from the TCS
	vec2 texCoord;
} IN[];			//Equal to TCS layout size

out Vertex	{ 	//Each TES works on a single vertex!
	vec2 texCoord;
} OUT;

vec3	QuadMixVec3(vec3 a, vec3 b, vec3 c, vec3 d) {
	vec3 p0 		 = mix(a,c, gl_TessCoord.x);
	vec3 p1 		 = mix(b,d, gl_TessCoord.x);
	
	return mix(p0,p1,gl_TessCoord.y);
}

vec2	QuadMixVec2(vec2 a, vec2 b, vec2 c, vec2 d) {
	vec2 p0 		 = mix(a,c, gl_TessCoord.x);
	vec2 p1 		 = mix(b,d, gl_TessCoord.x);
	
	return mix(p0,p1,gl_TessCoord.y);
}

void main()	{			 		
	vec3 combinedPos = QuadMixVec3(	gl_in[0].gl_Position.xyz ,
												gl_in[1].gl_Position.xyz ,
												gl_in[2].gl_Position.xyz ,
												gl_in[3].gl_Position.xyz	);

	OUT.texCoord = QuadMixVec2(IN[0].texCoord, 
										IN[1].texCoord,
										IN[2].texCoord,
										IN[3].texCoord	);
	
	vec4 worldPos = modelMatrix * vec4(combinedPos, 1);
	
	float height = texture(heightMap, OUT.texCoord  ).x;
	
	worldPos.y += height * 50;
		
	gl_Position = projMatrix * viewMatrix * worldPos;
}
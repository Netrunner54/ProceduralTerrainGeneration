#version 460

layout (vertices=4) out;

uniform mat4 uView;
uniform int uHighQuality;

in vec2 vTexCoord[];

out vec2 tTexCoord[];

void main()
{
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	tTexCoord[gl_InvocationID] = vTexCoord[gl_InvocationID];

	if (gl_InvocationID == 0)
	{
		// max tesselation on each patch
		if (uHighQuality == 1)
		{
			gl_TessLevelOuter[0] = 64.0; // left
			gl_TessLevelOuter[1] = 64.0; // bottom
			gl_TessLevelOuter[2] = 64.0; // right
			gl_TessLevelOuter[3] = 64.0; // top
			
			gl_TessLevelInner[0] = 64.0; // u
			gl_TessLevelInner[1] = 64.0; // v
		}
		// optimized tesselation
		else
		{
			const float MIN_TESSELATION_LEVEL = 2.0;
			const float MAX_TESSELATION_LEVEL = 6.0;
			const float MIN_DISTANCE = 16.0;
			const float MAX_DISTANCE = 1024.0;
			
			// distances to patch corners
			float distance00 = clamp(distance(uView * gl_in[0].gl_Position, vec4(0.0, 0.0, 0.0, 1.0) - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
			float distance10 = clamp(distance(uView * gl_in[1].gl_Position, vec4(0.0, 0.0, 0.0, 1.0) - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
			float distance01 = clamp(distance(uView * gl_in[2].gl_Position, vec4(0.0, 0.0, 0.0, 1.0) - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
			float distance11 = clamp(distance(uView * gl_in[3].gl_Position, vec4(0.0, 0.0, 0.0, 1.0) - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE), 0.0, 1.0);
			
			// caclulating tesselation level to each corner
			float tesselation_level0 = floor(mix(MAX_TESSELATION_LEVEL, MIN_TESSELATION_LEVEL, min(distance00, distance01)));
			float tesselation_level1 = floor(mix(MAX_TESSELATION_LEVEL, MIN_TESSELATION_LEVEL, min(distance00, distance10)));
			float tesselation_level2 = floor(mix(MAX_TESSELATION_LEVEL, MIN_TESSELATION_LEVEL, min(distance10, distance11)));
			float tesselation_level3 = floor(mix(MAX_TESSELATION_LEVEL, MIN_TESSELATION_LEVEL, min(distance01, distance11)));
			
			// outer tesselation
			gl_TessLevelOuter[0] = pow(2, tesselation_level0); // left
			gl_TessLevelOuter[1] = pow(2, tesselation_level1); // bottom
			gl_TessLevelOuter[2] = pow(2, tesselation_level2); // right
			gl_TessLevelOuter[3] = pow(2, tesselation_level3); // top
			
			// inner tesselation
			gl_TessLevelInner[0] = max(gl_TessLevelOuter[0], gl_TessLevelOuter[2]); // u
			gl_TessLevelInner[1] = max(gl_TessLevelOuter[1], gl_TessLevelOuter[3]); // v
		}
	}
}
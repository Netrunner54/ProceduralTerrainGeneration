#version 460

layout (quads, fractional_odd_spacing, ccw) in;

uniform mat4 uVP;
uniform sampler2D uHeightMap;

in vec2 tTexCoord[];

out float Height;

void main()
{
	// patch coordinate
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	// texture coordinate
	vec2 t00 = tTexCoord[0]; // bottom left
	vec2 t10 = tTexCoord[1]; // top left
	vec2 t01 = tTexCoord[2]; // bottom right
	vec2 t11 = tTexCoord[3]; // top right

	// linear interpolation of texture coordinates
	vec2 t0 = (t10 - t00) * u + t00;
	vec2 t1 = (t11 - t01) * u + t01;
	vec2 texCoord = (t1 - t0) * v + t0;

	Height = texture(uHeightMap, texCoord).r * 256.0;

	// vertex coordinates
	vec4 p00 = gl_in[0].gl_Position; // bottom left
	vec4 p10 = gl_in[1].gl_Position; // top left
	vec4 p01 = gl_in[2].gl_Position; // bottom right
	vec4 p11 = gl_in[3].gl_Position; // top right


	// surface normal
	vec4 uVec = p10 - p00;
	vec4 vVec = p01 - p00;
	vec4 normal = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0.0));

	// interpolation of vertex position coordinates across the patch
	vec4 p0 = (p10 - p00) * u + p00;
	vec4 p1 = (p11 - p01) * u + p01;
	vec4 pos = (p1 - p0) * v + p0;

	pos += normal * Height;

	// vertex position in clip space
	gl_Position = uVP * pos; 
}
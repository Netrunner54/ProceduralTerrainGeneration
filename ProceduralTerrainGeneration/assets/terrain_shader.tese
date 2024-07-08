#version 460

layout (quads, fractional_odd_spacing, ccw) in;

uniform mat4 uVP;
uniform sampler2D uHeightMap;
uniform float uMaxHeight = 256.0;

in vec2 tcTexCoord[];

out float teHeight;
out vec2 teTexCoords;

void main()
{
	// patch coordinate
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	// texture coordinate
	vec2 t00 = tcTexCoord[0]; // bottom left
	vec2 t10 = tcTexCoord[1]; // top left
	vec2 t01 = tcTexCoord[2]; // bottom right
	vec2 t11 = tcTexCoord[3]; // top right

	// linear interpolation of texture coordinates
	vec2 t0 = (t10 - t00) * u + t00;
	vec2 t1 = (t11 - t01) * u + t01;
	vec2 texCoord = (t1 - t0) * v + t0;

	teTexCoords = texCoord;


  // sampling height from a texture
	teHeight = texture(uHeightMap, texCoord).r * uMaxHeight;

	// vertex coordinates
	vec4 p00 = gl_in[0].gl_Position; // bottom left
	vec4 p10 = gl_in[1].gl_Position; // top left
	vec4 p01 = gl_in[2].gl_Position; // bottom right
	vec4 p11 = gl_in[3].gl_Position; // top right


	// surface normal
	vec4 uVec = p10 - p00;
	vec4 vVec = p01 - p00;
	vec4 up = normalize(vec4(cross(vVec.xyz, uVec.xyz), 0.0));

	// interpolation of vertex position coordinates across the patch
	vec4 p0 = (p10 - p00) * u + p00;
	vec4 p1 = (p11 - p01) * u + p01;
	vec4 pos = (p1 - p0) * v + p0;

	pos += up * teHeight;

	// vertex position in clip space
	gl_Position = uVP * pos; 
}
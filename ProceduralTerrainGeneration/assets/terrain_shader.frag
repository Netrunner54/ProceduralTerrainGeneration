#version 460

//in float teHeight;
in vec2 teTexCoords;

uniform sampler2D uNormalMap;
uniform sampler2D uDiffuseMap;

uniform bool uNormalMode = false;

uniform vec3 uLightDir;// = vec3(0.3, 1.0, 0.4);

out vec4 fColor;

void main()
{
	// NOTE: green and blue are switch so we do not have to transform normals
	vec3 normal = texture(uNormalMap, teTexCoords).rbg * 2.0 - 1.0; // converting vector from rgb space to normal space

	if (uNormalMode)
		fColor = vec4(normal, 1.0);
	else
  {
		vec3 color = texture(uDiffuseMap, teTexCoords).rgb;
		fColor = vec4(color * max(dot(normalize(uLightDir), normal), 0.0), 1.0) + vec4(color * 0.2, 1.0);	
	}

}
#version 460

in float Height;
in vec3 Normal;

out vec4 fColor;

void main()
{
	float altitude = (Height) / 128.0;

	// setting pixel color based on altitude
	if (altitude <= 0.01)				// sea
		fColor = vec4(0.0, 0.2, 0.282, 1.0);
	else if (altitude < 0.01)			// beaches
		fColor = vec4(0.62, 0.65, 0.23, 1.0);
	else if (altitude < 0.3)			// fields/forests
		fColor = vec4(0.0, mix(0.6, 0.25, altitude/0.3), mix(0.1, 0.0, altitude/0.3), 1.0);
	else if (altitude < 0.8)			// mountains
		fColor = vec4(vec3(mix(0.15, 0.35, (altitude-0.3)/0.4)), 1.0);
	else								// peaks
		fColor = vec4(vec3(mix(0.8, 0.95, (altitude-0.6)/0.4)), 1.0);

	//fColor = vec4(vec3(1.0) * (Height / 64.0), 1.0);
}
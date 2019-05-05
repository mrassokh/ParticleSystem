#version 400 core
layout (location = 0) in vec4 vertex;
//layout (location = 1) in vec4 color;
layout (location = 2) in mat4 model;

out vec4 colorBuf;

//uniform mat4 projection;
//uniform mat4 view;
uniform mat4 projection_view;
uniform	vec3	cursorPoint;

#define	COLOR_MAX	vec4(1.0f, 1.0f, 1.0f, 0.1f)
#define	COLOR_MIN	vec4(0.7f, 0.5f, 0.6f, 0.1f)

void main()
{
	float	distance = length(cursorPoint - vertex.xyz);
	colorBuf = mix(COLOR_MIN, COLOR_MAX, distance / 2);//vec4(1.0f, 0.5f, 0.2f, 1.0f);//color;
	gl_Position = projection_view * model * vec4(vertex.xyz, 1.0);
}

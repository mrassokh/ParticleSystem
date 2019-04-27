#version 400 core
layout (location = 0) in vec4 vertex;

out vec4 colorBuf;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * vec4(vertex.xyz, 1.0);
	colorBuf = color;
}

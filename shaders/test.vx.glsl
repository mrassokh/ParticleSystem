#version 400 core
//layout (location = 0) in vec4 vertex;
layout (location = 0) in vec3 vertex;
out vec4 colorBuf;

//uniform mat4 projection;
//uniform mat4 view;

void main()
{
    //gl_Position = projection * view * vec4(vertex.xyz, 1.0);
	gl_Position = vec4(vertex.xyz, 1.0);
	colorBuf = color;
	colorBuf = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

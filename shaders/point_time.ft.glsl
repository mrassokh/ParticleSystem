#version 400 core
in vec4 	colorBuf;
in	vec2  	isLive;
out vec4 	color;


void main()
{
	if	(isLive.x < 0.1f)
		discard;
    color = colorBuf;
}

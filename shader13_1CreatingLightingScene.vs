#version 330 core
layout (location = 0) in vec3 aPos;
// 这里接收了纹理坐标，但是没有将它传递下去，所以后面fragment shader纹理构成后是黑的
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
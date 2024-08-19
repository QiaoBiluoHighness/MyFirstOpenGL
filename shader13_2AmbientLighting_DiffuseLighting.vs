#version 330 core
// 相对于shader13_1CreatingLightingScene.vs
// 坐标多了法向量属性，纹理坐标不需要
// 将法向量传递到下一个pipeline
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec4 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = aNormal;
}
#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float temp;

out vec4 TempColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TempColor = vec4(temp, 0.5f - 2 * (temp - 0.5f) * (temp - 0.5f), 1 - temp, 0.0f);
}
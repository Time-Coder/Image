#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 transformation;
out vec4 ourColor;

void main()
{
    gl_Position = transformation * vec4(aPos, 0.0f, 1.0f);
    ourColor = aColor;
}
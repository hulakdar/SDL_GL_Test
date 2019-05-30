#version 330 core

in vec4 Position; 

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * Position;
}
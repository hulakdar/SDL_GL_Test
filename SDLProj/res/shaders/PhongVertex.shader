#version 330 core

layout(location = 0) in vec4 Position; 
layout(location = 1) in vec2 TexCoord; 
layout(location = 2) in vec3 Normal;

out vec3 v_FragmentPosition;
out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
uniform mat3 u_NormalRot;

void main()
{
	v_FragmentPosition = (u_Model * Position).xyz;
	v_TexCoord = vec2(TexCoord.x, 1 - TexCoord.y);
	v_Normal = u_NormalRot * Normal;

	gl_Position = u_ViewProjection * vec4(v_FragmentPosition, 1.f);
}
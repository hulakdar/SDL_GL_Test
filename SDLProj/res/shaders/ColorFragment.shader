#version 330 core

in vec2 v_TexCoord;

out vec4 Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 Texel = texture(u_Texture, v_TexCoord);
	if (Texel.a == 0.0f)
		discard;
	Color = Texel;
}
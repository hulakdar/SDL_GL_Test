#version 330 core

in vec3 v_FragmentPosition;
in vec2 v_TexCoord;
in vec3 v_Normal;

out vec4 Color;

uniform vec4 u_Color;
uniform vec3 u_LightPosition;
uniform sampler2D u_Texture;

const float AmbientStrength = 0.1f;
const float SpecularStrength = 0.2f;

void main()
{
	vec4 Texel = texture(u_Texture, v_TexCoord);
	if (Texel.a < 0.1f)
		discard;
	vec3 TexColor = Texel.xyz;
	float Opacity = Texel.a;

	vec3 Ambient = TexColor * AmbientStrength;
	vec3 LightDirection = normalize(u_LightPosition - v_FragmentPosition);
	vec3 Diffuse = TexColor * max(dot(LightDirection, v_Normal), 0.f);
	vec3 ViewDirection = normalize(vec3(0,0,-3)-v_FragmentPosition);
	vec3 ReflectDirection = reflect(-LightDirection, v_Normal);
	vec3 Specular = pow(max(-dot(ViewDirection, ReflectDirection), 0.f), 32) * SpecularStrength * u_Color.xyz;
	Color = vec4(min(Ambient + Diffuse + Specular, 1.f), Opacity);
}
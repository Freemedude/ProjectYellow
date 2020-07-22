#version 450


in vec3 v_oNormal;
in vec3 v_wNormal;

in vec3 v_position;

uniform vec4 u_color;
uniform vec3 u_lightDirection;
uniform vec3 u_ambientColor;
uniform float u_ambientIntensity;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(v_wNormal);
    vec3 light = -normalize(u_lightDirection);

    float attenuation = dot(normal, light);

    FragColor = u_color * attenuation;
}
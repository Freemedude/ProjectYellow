#version 450

in vec3 v_normal;
in vec3 v_position;

uniform vec4 u_color;

uniform vec3 u_lightDirection;

out vec4 FragColor;

void main()
{
    float lit = dot(u_lightDirection, v_normal);

    lit = clamp(lit, 0.1f, 1.0f);


    vec4 color = u_color * lit;

    FragColor = color;
}
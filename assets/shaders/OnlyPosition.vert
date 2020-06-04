#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 u_matrix;

out vec3 v_color;

// Hello
void main()
{
    vec4 pos = u_matrix * vec4(position, 1);

    v_color = color;
    gl_Position = pos;
}
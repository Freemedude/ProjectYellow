#version 450

#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 u_matrix;

out vec3 v_normal;
out vec4 v_position;


void main()
{
    v_normal = color;

    vec4 pos = u_matrix * vec4(position, 1);
    v_position = pos;
    gl_Position = pos;
}
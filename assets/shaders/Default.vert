#version 450

#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_modelView;
uniform mat4 u_mvp;

out vec3 v_oNormal;
out vec3 v_wNormal;

out vec4 v_position;


void main()
{
    v_oNormal = normal;
    v_wNormal = (u_model * vec4(normal, 0)).xyz;

    vec4 pos = u_mvp * vec4(position, 1);
    v_position = pos;
    gl_Position = pos;
}
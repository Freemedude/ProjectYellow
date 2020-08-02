#version 450

in vec3 position;
in vec3 normal;
in vec2 uv;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_modelView;
uniform mat4 u_mvp;

out vec3 v_oNormal;
out vec3 v_wNormal;
out vec2 v_uv;
out vec4 v_position;
out vec4 v_wPosition;


void main()
{
    v_oNormal = normal;
    v_wNormal = (u_model * vec4(normal, 0)).xyz;
    v_uv = uv;

    vec4 pos = u_mvp * vec4(position, 1);
    v_wPosition = u_model * vec4(position, 1);

    v_position = pos;
    gl_Position = pos;
}
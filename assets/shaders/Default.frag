#version 450


in vec3 v_oNormal;
in vec3 v_wNormal;

in vec3 v_position;

uniform vec4 u_color;
uniform vec3 u_lightDirection;
uniform vec3 u_ambientColor;
uniform float u_ambientIntensity;
uniform vec3 u_cameraPosition;


out vec4 FragColor;

vec3 ambient()
{
    return u_ambientColor * u_ambientIntensity * u_color.xyz;
}

void main()
{
    vec3 ambient = ambient();
    vec3 normal = normalize(v_wNormal);
    vec3 light = normalize(u_lightDirection);

    float attenuation = dot(normal, light);
    vec3 color = ambient + attenuation * u_color.xyz;

    FragColor = vec4(color, 1);
}
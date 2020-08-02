#version 450

//// Lighting
// Ambient
uniform vec3 u_ambientColor;
uniform float u_ambientIntensity;

// Directional
uniform vec3 u_lightDirection;
uniform vec3 u_sunColor;
uniform float u_specularStrength;

// Material properties
uniform vec4 u_color;
uniform float u_shininess;
uniform sampler2D imageTexture;

uniform vec3 u_cameraPosition;
in vec3 v_oNormal;
in vec3 v_wNormal;
in vec4 v_wPosition;
in vec2 v_uv;

out vec4 FragColor;

vec3 phong(
vec3 ambientColor, float ambientIntensity,
vec3 lightDirection, vec3 wsNormal, vec3 lightColor,
vec3 camPos, vec3 fragPos,
float specularStrength, float shininess);

vec3 ambient(vec3 ambientColor, float ambientIntensity);
vec3 diffuse(vec3 lightDirection, vec3 wsNormal, vec3 lightColor);
vec3 specular(vec3 camPos, vec3 fragPos, vec3 normal, vec3 lightDir,
vec3 lightColor, float specularStrength, float shininess);

void main()
{
    vec4 imageSample = texture(imageTexture, v_uv);
    vec3 normal = normalize(v_wNormal);

    vec3 lighting = phong(
    u_ambientColor, u_ambientIntensity,
    u_lightDirection, normal, u_sunColor,
    u_cameraPosition, v_wPosition.xyz, u_specularStrength, u_shininess);

    vec3 color = (lighting + imageSample.rgb) * u_color.rgb;

    FragColor = vec4(color, 1);
}

vec3 phong(
vec3 ambientColor, float ambientIntensity,
vec3 lightDirection, vec3 wsNormal, vec3 lightColor,
vec3 camPos, vec3 fragPos,
float specularStrength, float shininess)
{
    vec3 ambient = ambient(ambientColor, ambientIntensity);
    vec3 diffuse = diffuse(wsNormal, lightDirection, lightColor);
    vec3 specular = specular(camPos, fragPos, wsNormal, lightDirection, lightColor, specularStrength, shininess);
    vec3 result = ambient + diffuse + specular;
    return result;
}

vec3 ambient(vec3 ambientColor, float ambientIntensity)
{
    vec3 result = ambientColor * ambientIntensity;
    return result;
}

vec3 diffuse(vec3 wsNormal, vec3 lightDirection, vec3 lightColor)
{
    float angle = max(dot(wsNormal, lightDirection), 0);
    vec3 result = lightColor * angle;
    return result;
}

vec3 specular(
vec3 camPos, vec3 fragPos, vec3 normal, vec3 lightDirection,
vec3 lightColor, float specularStrength, float shininess)
{
    vec3 viewDir = normalize(camPos - fragPos);
    vec3 refl = reflect(-lightDirection, normal);

    float angle = max(dot(viewDir, refl), 0);
    float spec = pow(angle, shininess);

    vec3 result = spec * specularStrength * lightColor;
    return result;
}

#version 430

in vec3 LightIntensity;
in vec2 Texcoords;

uniform sampler2D texture1;

layout( location = 0 ) out vec4 FragColor;

void main() {
    vec3 textureColor = texture(texture1, Texcoords).rgb;
    FragColor = vec4(LightIntensity * textureColor, 1.0);
}

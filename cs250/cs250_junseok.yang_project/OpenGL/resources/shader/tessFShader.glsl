#version 450 core

out vec4 FragColor;

in vec3 gNormal;

uniform vec3 LightPosition;
uniform vec3 tesscolor;

void main()
{
    vec3 normal=normalize(gNormal);
    vec3 L=normalize(LightPosition);
    float nl = abs(dot(normal,L));
    
    FragColor = vec4(tesscolor * nl, 1.0);
}

#version 450 core
out vec4 FragColor;

uniform vec3 grass_color;

void main()
{
    FragColor = vec4(grass_color, 1.0);
}

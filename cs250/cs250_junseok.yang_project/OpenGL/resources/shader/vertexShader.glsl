#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat3 normalMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = normalMatrix * aNormal; 
    FragPos = (view * model * vec4(aPos, 1.0)).xyz;
    
    gl_Position = projection * vec4(FragPos, 1.0);
}
#version 330 core

layout (location =0)in vec2 vtPosition;
layout (location =1)in vec4 vtColor;
layout (location =2)in vec2 vtUV;

out vec2 frPosition;
out vec4 frColor;
out vec2 frUV;

uniform mat3 P;

void main(){
   vec3 p = vec3(vtPosition,1.0);
   vec3 ndc = P * p;
   gl_Position = vec4(ndc.xy,0.0,1.0);
   frColor = vtColor;
   frUV = vtUV;

}
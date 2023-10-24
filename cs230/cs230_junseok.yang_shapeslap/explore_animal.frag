/*
junseok.yang
shape_lap
cs230
spring 2019
explore_animal.frag
*/
#version 330
out vec4 output_color;
in vec4 interpolated_color;
uniform float time;

void main(){
    output_color = interpolated_color;
}
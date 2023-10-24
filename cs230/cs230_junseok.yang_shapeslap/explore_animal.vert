/*
junseok.yang
shape_lap
cs230
spring 2019
explore_animal.vert
*/
#version 330
in vec2 position;
in vec4 vert_color;
in vec2 texture_coordiante;
uniform mat3 to_ndc;
uniform float time;
out vec4 interpolated_color;

void main(){
    vec3 p = vec3(position,1.0);
    float t = sin(time);
    float angle = texture_coordiante.x;
    float distance = texture_coordiante.y;
    p.x += t * cos(angle) * distance;
    p.y += t * sin(angle) * distance;
    vec3 ndc_version= to_ndc*p;
    gl_Position = vec4(ndc_version.x,ndc_version.y, 0.0, 1.0);
    interpolated_color=vert_color;
}   
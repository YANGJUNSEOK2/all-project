#version 330
uniform vec4 color;
out vec4 output_color;
in float funfactor;
in vec4 interpolated_color;
uniform float time;

void main(){
    vec4 c=vec4(0.1+0.5*cos(0.5*time), -0.2, 0.2, 0.0);
    output_color = 
    interpolated_color+
    color + c*funfactor*4.0;
}
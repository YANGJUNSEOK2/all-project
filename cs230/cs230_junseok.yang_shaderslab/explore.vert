#version 330
in vec2 position;
in vec4 vert_color;
uniform mat3 to_ndc;
uniform float time;
uniform float mouse_x;
uniform float mouse_y;
out float funfactor;
out vec4 interpolated_color;

void main(){
	vec2 mouse = vec2(mouse_x-580, -mouse_y+320);
    vec3 p = vec3(position, 1.0);
    p += vec3(mouse+(position)*(sin(time)*cos(time)), 0);
    vec3 ndc_version = to_ndc * p;
    gl_Position = 
    vec4(ndc_version.xy, 0.0, 1.0);

    funfactor = (ndc_version.x);
    interpolated_color = vert_color;
}


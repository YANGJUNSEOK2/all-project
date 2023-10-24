#version 450 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform float time;

float PHI = 1.61803398874989484820459;
float gold_noise(vec2 xy, float seed){
       return fract( tan( distance( xy * PHI, xy ) * seed ) * xy.x );
}

void main() {
    FragColor = vec4(gold_noise( gl_FragCoord.xy, fract( time ) + 1.0 ),
                gold_noise( gl_FragCoord.xy, fract( time ) + 2.0 ),
                gold_noise( gl_FragCoord.xy, fract( time ) + 3.0 ),
                1.0 );
}
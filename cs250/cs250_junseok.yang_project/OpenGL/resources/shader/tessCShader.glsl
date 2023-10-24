#version 450 core

layout(vertices = 3)out;

in vec3 vPosition[];
out vec3 tcPosition[];

uniform float TessLevelInner;
uniform float TessLevelOuter;

uniform mat4 Modelview;

float map(float input_value,float input_start,float input_end,float output_start,float output_end)
{
    float t=(input_value-input_start)/(input_end-input_start);
    float result=mix(output_start,output_end,t);
    return result;
}

void main()
{
    tcPosition[gl_InvocationID]=vPosition[gl_InvocationID];
    
    gl_TessLevelInner[0] = TessLevelInner;
    
    gl_TessLevelOuter[0] = TessLevelOuter;
    gl_TessLevelOuter[1] = TessLevelOuter;
    gl_TessLevelOuter[2] = TessLevelOuter;
}

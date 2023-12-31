#version 450 core

layout(triangles)in;
layout(line_strip,max_vertices=6)out;

uniform mat3 NormalMatrix;
uniform mat4 Projection;
uniform mat4 Modelview;
uniform float Shrink=.9;
out vec3 gNormal;

vec3 Verts[3];
vec3 Center;
vec3 Normal;

void EmitShrunkVertex(int i)
{
    vec3 move_direction=Verts[i]-Center;
    gl_Position=Projection*Modelview*vec4(Center+Shrink*move_direction,1);
    gNormal=Normal;
    EmitVertex();
}

void main()
{
    Verts[0]=gl_in[0].gl_Position.xyz;
    Verts[1]=gl_in[1].gl_Position.xyz;
    Verts[2]=gl_in[2].gl_Position.xyz;
    
    Center=(Verts[0]+Verts[1]+Verts[2])/3.;
    
    vec3 A=Verts[2]-Verts[0];
    vec3 B=Verts[1]-Verts[0];
    Normal=NormalMatrix*normalize(cross(A,B));
    
    EmitShrunkVertex(0);
    EmitShrunkVertex(1);
    EmitShrunkVertex(2);
    
    EndPrimitive();
}

#version 450 core

layout(triangles, equal_spacing, cw) in;

in vec3 tcPosition[];

void main()
{
    // vec3 gl_TessCoord -- normalized coordinates
    //  for tri interpret them as barycentric coords
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    float w = gl_TessCoord.z;

    vec3 p0=tcPosition[0]*u;
    vec3 p1=tcPosition[1]*v;
    vec3 p2=tcPosition[2]*w;

    vec3 point_on_triangle = p0+p1+p2;
    //vec3 point_on_unit_sphere = normalize(point_on_triangle);
    gl_Position = vec4(point_on_triangle, 1);
}

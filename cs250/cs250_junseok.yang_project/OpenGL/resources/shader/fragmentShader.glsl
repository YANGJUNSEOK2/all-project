#version 450 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;

uniform bool show_fog = false; 
uniform bool show_toon = false;

uniform struct LightInfo {
  vec3 Position;  // Light position in eye coords.
  vec3 La;        // Ambient light intesity
  vec3 L;         // Diffuse and specular light intensity
} Light;

uniform struct MaterialInfo {
  vec3 Ka;            // Ambient reflectivity
  vec3 Kd;            // Diffuse reflectivity
  vec3 Ks;            // Specular reflectivity
  float Shininess;    // Specular shininess factor
} Material;

uniform struct FogInfo {
  float MaxDist;
  float MinDist;
  vec3 Color;
} Fog;

uniform int levels;
const float scaleFactor = 1.0 / levels;

vec3 blinnPhong( vec3 position, vec3 n ) {  
  vec3 ambient = Light.La * Material.Ka;
  vec3 s = normalize( Light.Position.xyz - position );
  float sDotN = max( dot(s,n), 0.0 );
  vec3 diffuse = Material.Kd * sDotN;
  vec3 spec = vec3(0.0, 0.0, 0.0);
  if( sDotN > 0.0 ) {
    vec3 v = normalize(-position.xyz);
    vec3 h = normalize( v + s );
    spec = Material.Ks *
            pow( max( dot(h,n), 0.0 ), Material.Shininess );
  }
  return ambient + Light.L * (diffuse + spec);
}

vec3 fogShade(){
    float dist = abs( FragPos.z );
    float fogFactor = (Fog.MaxDist - dist) /
                      (Fog.MaxDist - Fog.MinDist);
    fogFactor = clamp( fogFactor, 0.0, 1.0 );
    vec3 shadeColor = blinnPhong(FragPos, normalize(Normal));
    vec3 color = mix( Fog.Color, shadeColor, fogFactor);
    return color;
}

vec3 toonShade( ) {
    vec3 n = normalize( Normal );
    vec3 s = normalize( Light.Position.xyz);
    vec3 ambient = Light.La * Material.Ka;
    float sDotN = max( dot( s, n ), 0.0 );
    vec3 diffuse = Material.Kd * floor( sDotN * levels ) * scaleFactor;

    return ambient + Light.L * diffuse;
}

void main() {

    if(show_fog)
        FragColor = vec4(fogShade(), 1.0);
    else if(show_toon)
        FragColor = vec4(toonShade(), 1.0);
    else
        FragColor = vec4(blinnPhong(FragPos, normalize(Normal)), 1.0);
}
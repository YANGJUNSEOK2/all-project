#version 330 core

in vec2 frPosition;
in vec4 frColor;
in vec2 frUV;

out vec4 color;

//uniform float time;
uniform sampler2D shaderTexture;

void main(){

    vec4 textureColor = texture(shaderTexture,frUV);

    color = frColor * textureColor;
}
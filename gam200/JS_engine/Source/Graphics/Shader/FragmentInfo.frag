#version 330 core

layout (location = 0) out vec4 Color;

uniform vec4 ColorInput;
uniform vec2 LightPosition;

in DATA {
	vec4 Position;
	vec4 Color;
} FragmentShader;

void main() {
	float Intensity = 1.0 / length(FragmentShader.Position.xy - LightPosition);
	Color = FragmentShader.Color * Intensity;
}
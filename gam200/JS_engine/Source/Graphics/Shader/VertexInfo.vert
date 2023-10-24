#version 330 core

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Color;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix  = mat4(1.0);
uniform mat4 ModelMatrix = mat4(1.0);

out DATA {
	vec4 Position;
	vec4 Color;
} VertexShader;

void main() {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * Position;
	VertexShader.Position = ModelMatrix * Position;
	VertexShader.Color = Color;
}
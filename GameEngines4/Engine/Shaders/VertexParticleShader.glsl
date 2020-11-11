#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;

out vec2 TexCoords;

uniform mat4 view; 
uniform mat4 proj;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0f);
    TexCoords = textureCoordinates;
}
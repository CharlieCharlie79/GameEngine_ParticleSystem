#version 450 core

in vec2 TexCoords;
 
uniform vec4 colour;

out vec4 Color;

uniform sampler2D textureID;

void main()
{
	vec4 newColour = texture(textureID, TexCoords) * colour;
	Color = newColour;
}
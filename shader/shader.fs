#version 330 core
out vec4 FragColor;

uniform float Time;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}; 

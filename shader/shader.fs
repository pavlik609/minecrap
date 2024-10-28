#version 330 core
out vec4 FragColor;

uniform float Time;
in vec2 TexCoord;

uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, TexCoord);
}; 

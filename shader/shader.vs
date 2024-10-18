#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform float Time;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos+0.5f*sin(Time+aPos.x+0.5f*aPos.y), 1.0);
    TexCoord = aTexCoord+sin(Time+aPos.x+0.5f*aPos.y);
};

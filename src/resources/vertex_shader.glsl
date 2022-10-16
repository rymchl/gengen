#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform vec2 vertex_offset;


void main()
{
    TexCoords = aTexCoords;    
    gl_Position = vec4(aPos, 1.0) + vec4(vertex_offset.x, vertex_offset.y, 0, 0);
}
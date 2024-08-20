#version 330 core

uniform mat4 locPVM;

layout (location = 0) in vec3 aPos;

void main()
{
   gl_Position = locPVM * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
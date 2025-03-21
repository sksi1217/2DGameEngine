#version 330 core

layout(location=0)in vec3 aPosition;// Позиция вершины
layout(location=1)in vec2 aTexCoord;// Текстурные координаты

out vec2 TexCoord;

void main()
{
	gl_Position=vec4(aPosition,1.);
	TexCoord=aTexCoord;
}

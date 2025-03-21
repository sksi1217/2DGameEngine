#version 330 core

layout(location=0)in vec3 aPosition;// Координаты вершины
layout(location=1)in vec2 aTexCoord;// Текстурные координаты

uniform mat4 transform;// Матрица преобразования

out vec2 TexCoord;

void main()
{
	gl_Position=transform*vec4(aPosition,1.);
	TexCoord=aTexCoord;
}

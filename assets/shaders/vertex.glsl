#version 330 core

layout(location=0)in vec2 aPos;// Позиция вершины
layout(location=1)in vec2 aTexCoord;// Текстурные координаты

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position=projection*view*model*vec4(aPos,0.,1.);
	TexCoord=aTexCoord;
}

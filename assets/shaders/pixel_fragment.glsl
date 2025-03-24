#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;// Исходная текстура
uniform float pixelSize;// Размер пикселя

void main()
{
	// Вычисляем новые текстурные координаты с учетом пикселизации
	vec2 pixelatedCoord=floor(TexCoord*pixelSize)/pixelSize;
	
	// Получаем цвет из текстуры с использованием новых координат
	FragColor=texture(texture1,pixelatedCoord);
}

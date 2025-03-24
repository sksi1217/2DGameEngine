#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;// Исходная текстура
uniform float blurRadius;// Радиус размытия
uniform vec2 texOffset;// Смещение текстурных координат

void main()
{
	// Ядро размытия (простое усреднение)
	vec4 color=vec4(0.);
	int radius=int(blurRadius);
	
	for(int i=-radius;i<=radius;++i)
	{
		vec2 offset=vec2(i,0)*texOffset;// Горизонтальное размытие
		color+=texture(texture1,TexCoord+offset);
	}
	
	// Нормализация результата
	color/=float(2*radius+1);
	
	FragColor=color;
}

#ifndef ENGINE_H
#define ENGINE_H

#include <math.h> // Для математических функций
#include <vector>
#include <GL/glew.h>

//----------------------------------------------------------------------------------
// Версия движка
//----------------------------------------------------------------------------------
#define ENGINE_VERSION_MAJOR 1
#define ENGINE_VERSION_MINOR 0
#define ENGINE_VERSION_PATCH 0
#define ENGINE_VERSION "1.0.0"

//----------------------------------------------------------------------------------
// Базовые определения
//----------------------------------------------------------------------------------
#ifndef PI
#define PI 3.14159265358979323846f
#endif
#ifndef DEG2RAD
#define DEG2RAD (PI / 180.0f)
#endif
#ifndef RAD2DEG
#define RAD2DEG (180.0f / PI)
#endif

//----------------------------------------------------------------------------------
// Базовые типы данных
//----------------------------------------------------------------------------------

// Вектор с 2 компонентами
typedef struct Vector2
{
	float x; // Компонента x
	float y; // Компонента y
} Vector2;

// Цвет (RGBA)
typedef struct Color
{
	unsigned char r; // Красный канал
	unsigned char g; // Зеленый канал
	unsigned char b; // Синий канал
	unsigned char a; // Альфа-канал (прозрачность)
} Color;

// Прямоугольник
typedef struct Rect
{
	float x, y; // Позиция
	float w, h; // Ширина и высота
} Rect;

// Текстура (хранится в GPU)
typedef struct Texture2D
{
	unsigned int id; // ID текстуры OpenGL
	int width;		 // Ширина текстуры
	int height;		 // Высота текстуры

	void Bind() const // ! делает текстуру активной
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
} Texture2D;

// Функция для генерации массива вершин
inline std::vector<float> GenerateVertices(const Rect &rect)
{
	std::vector<float> vertices = {
		rect.x, rect.y, 0.0f, 0.0f, 0.0f,					// Левый нижний угол
		rect.x + rect.w, rect.y, 0.0f, 1.0f, 0.0f,			// Правый нижний угол
		rect.x + rect.w, rect.y + rect.h, 0.0f, 1.0f, 1.0f, // Правый верхний угол
		rect.x, rect.y + rect.h, 0.0f, 0.0f, 1.0f			// Левый верхний угол
	};
	return vertices;
}

/*
//----------------------------------------------------------------------------------
// Предопределенные цвета
//----------------------------------------------------------------------------------
#define LIGHTGRAY CLITERAL(Color){200, 200, 200, 255} // Светло-серый
#define GRAY CLITERAL(Color){130, 130, 130, 255}	  // Серый
#define DARKGRAY CLITERAL(Color){80, 80, 80, 255}	  // Темно-серый
#define YELLOW CLITERAL(Color){253, 249, 0, 255}	  // Желтый
#define GOLD CLITERAL(Color){255, 203, 0, 255}		  // Золотой
#define ORANGE CLITERAL(Color){255, 161, 0, 255}	  // Оранжевый
#define PINK CLITERAL(Color){255, 109, 194, 255}	  // Розовый
#define RED CLITERAL(Color){230, 41, 55, 255}		  // Красный
#define MAROON CLITERAL(Color){190, 33, 55, 255}	  // Темно-красный
#define GREEN CLITERAL(Color){0, 228, 48, 255}		  // Зеленый
#define LIME CLITERAL(Color){0, 158, 47, 255}		  // Лайм
#define DARKGREEN CLITERAL(Color){0, 117, 44, 255}	  // Темно-зеленый
#define SKYBLUE CLITERAL(Color){102, 191, 255, 255}	  // Небесно-голубой
#define BLUE CLITERAL(Color){0, 121, 241, 255}		  // Синий
#define DARKBLUE CLITERAL(Color){0, 82, 172, 255}	  // Темно-синий
#define PURPLE CLITERAL(Color){200, 122, 255, 255}	  // Фиолетовый
#define VIOLET CLITERAL(Color){135, 60, 190, 255}	  // Сиреневый
#define DARKPURPLE CLITERAL(Color){112, 31, 126, 255} // Темно-фиолетовый
#define BEIGE CLITERAL(Color){211, 176, 131, 255}	  // Бежевый
#define BROWN CLITERAL(Color){127, 106, 79, 255}	  // Коричневый
#define DARKBROWN CLITERAL(Color){76, 63, 47, 255}	  // Темно-коричневый

#define WHITE CLITERAL(Color){255, 255, 255, 255}	 // Белый
#define BLACK CLITERAL(Color){0, 0, 0, 255}			 // Черный
#define BLANK CLITERAL(Color){0, 0, 0, 0}			 // Прозрачный
#define MAGENTA CLITERAL(Color){255, 0, 255, 255}	 // Маджента
#define RAYWHITE CLITERAL(Color){245, 245, 245, 255} // Свой белый

//----------------------------------------------------------------------------------
// Inline функции
//----------------------------------------------------------------------------------
inline float Vector2Length(Vector2 v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

inline Vector2 Vector2Normalize(Vector2 v)
{
	float length = Vector2Length(v);
	return (Vector2){v.x / length, v.y / length};
}

inline Vector2 Vector2Add(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x + v2.x, v1.y + v2.y};
}
*/

#endif // ENGINE_H

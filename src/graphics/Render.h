#include <src/graphics/Texture2D.h>
#include <src/graphics/Shader.h>
#include <src/core/Rect.h>

class Render
{
public:
	Render();
	~Render();

	// srcrect - выбрать какую часть текстуры отрисовывать \\ dstrect - позиция и размер объекта
	void RenderSprite(Texture2D *texture, Shader *shader, const Rect *srcrect, const Rect *dstrect, const double angle, const Rect *origin);

private:
	GLuint VAO, VBO;
};

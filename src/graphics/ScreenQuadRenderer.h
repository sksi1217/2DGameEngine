#include <GL/glew.h>

class ScreenQuadRenderer
{
private:
	GLuint VAO, VBO;

public:
	ScreenQuadRenderer();

	~ScreenQuadRenderer()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Render()
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
};

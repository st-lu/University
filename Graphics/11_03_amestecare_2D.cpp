// Codul sursa este adaptat dupa OpenGLBook.com
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"

static bool galbenPrimul = GL_TRUE;
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId;

void CreateVBO(void)
{
	// coordonatele varfurilor
	GLfloat Vertices[] =
	{
	  -0.6f, -0.6f, 0.0f, 1.0f,
	  -0.6f,  0.6f, 0.0f, 1.0f,
	   0.3f,  0.0f, 0.0f, 1.0f,
	   0.6f, -0.6f, 0.0f, 1.0f,
	   0.6f,  0.6f, 0.0f, 1.0f,
	  -0.3f,  0.0f, 0.0f, 1.0f,
	};
	// culorile, ca atribute ale varfurilor
	GLfloat Colors[] =
	{
	  1.0f, 1.0f, 0.0f, 0.5f,
	  1.0f, 1.0f, 0.0f, 0.5f,
	  1.0f, 1.0f, 0.0f, 0.5f,
	  0.0f, 1.0f, 1.0f, 0.5f,
	  0.0f, 1.0f, 1.0f, 0.5f,
	  0.0f, 1.0f, 1.0f, 0.5f,
	};

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

void CreateShaders(void)
{
	ProgramId = LoadShaders("11_03_Shader.vert", "11_03_Shader.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	CreateVBO();
	CreateShaders();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 't':
	case 'T':
		galbenPrimul = !galbenPrimul;
		glutPostRedisplay();
		break;
	case 27:  /*  Escape key  */
		exit(0);
		break;
	default:
		break;
	}
}
void RenderFunction(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

	if (galbenPrimul) {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glDisable(GL_BLEND);
	glutPostRedisplay();
	glFlush();
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
	glutInitWindowSize(1000, 600); //dimensiunile ferestrei
	glutCreateWindow("Amestecare"); // titlul ferestrei
	glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutKeyboardFunc(keyboard);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}


/* Trasarea unui cerc folosind reprezentarea parametrica */
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"
#include "glm/glm/glm.hpp"  
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
using namespace std;

const int NR_POINTS = 20;
float PI = 3.141592f;

GLuint
VaoId,
VboId,
EboId,
ColorBufferId,
ProgramId,
myMatrixLocation,
codColLocation;

int codCol;
GLint winWidth = 1000, winHeight = 600;
float width = winWidth / 10, height = winHeight / 10;
float cx = 10.0f, cy = 5.0f, radius = 20.0;

glm::mat4 myMatrix;

void CreateVBO(void)
{
	glm::vec4 vf_coord[NR_POINTS];
	for (int i = 0; i < NR_POINTS; i++)
	{
		// se foloseste reprezentarea parametrica pentru a genera varfurile (puncte situate pe cerc)
		vf_coord[i] =
			glm::vec4(cx + radius * cos(2 * PI * i / NR_POINTS),
				cy + radius * sin(2 * PI * i / NR_POINTS),
				0.0f, 1.0f);
	};
	// culorile varfurilor
	glm::vec4 vf_col[NR_POINTS];
	for (int i = 0; i < NR_POINTS; i++)
	{
		vf_col[i] = glm::vec4(abs(0.4 + 0.3 * i / NR_POINTS + cos(0.1 * i)), abs(0.6 + 0.4 * i / NR_POINTS + sin(0.1 * i)), abs(0.4 + 0.5 * i / NR_POINTS - sin(0.1 * i)), 1.0f);
	};
	// indicii
	GLuint vf_ind[NR_POINTS + 1 + 3 * (NR_POINTS - 2)];
	// indexare pentru trasarea conturului
	for (int i = 0; i <= NR_POINTS; i++)
		vf_ind[i] = i % NR_POINTS;
	// indexare pentru desenarea interiorului
	for (int i = 0; i < NR_POINTS - 2; i++)
	{
		vf_ind[NR_POINTS + 3 * i + 1] = 0;
		vf_ind[NR_POINTS + 3 * i + 2] = i + 1;
		vf_ind[NR_POINTS + 3 * i + 3] = i + 2;
	}

	// se creeaza un buffer nou pentru varfuri
	glGenBuffers(1, &VboId);
	// buffer pentru indici
	glGenBuffers(1, &EboId);
	// se creeaza / se leaga un VAO (Vertex Array Object)
	glGenVertexArrays(1, &VaoId);

	// legare VAO
	glBindVertexArray(VaoId);

	// buffer-ul este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);

	// buffer-ul va contine atat coordonatele varfurilor, cat si datele de culoare
	glBufferData(GL_ARRAY_BUFFER, sizeof(vf_coord) + sizeof(vf_col), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vf_coord), vf_coord);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vf_coord), sizeof(vf_col), vf_col);

	// buffer-ul pentru indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vf_ind), vf_ind, GL_STATIC_DRAW);

	// se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vf_coord));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &EboId);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
void CreateShaders(void)
{
	ProgramId = LoadShaders("09_01_Shader.vert", "09_01_Shader.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
	// creare VBO
	CreateVBO();
	CreateShaders();
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
}
void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	width = winWidth / 10, height = winHeight / 10;
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	myMatrix = glm::ortho(-width, width, -height, height);
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	// interiorul
	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glDrawElements(GL_TRIANGLES, 3 * (NR_POINTS - 2), GL_UNSIGNED_INT, (GLvoid*)((NR_POINTS + 1) * sizeof(GLuint)));
	// acelasi efect poate fi obtinut cu GL_TRIANGLE_FAN, utilizand multimea initiala de indici
	// glDrawElements(GL_TRIANGLE_FAN, NR_POINTS, GL_UNSIGNED_INT, (GLvoid*)(0));
	// conturul
	codCol = 1;
	glUniform1i(codColLocation, codCol);
	glLineWidth(2.0f);
	glDrawElements(GL_LINE_LOOP, NR_POINTS, GL_UNSIGNED_INT, (GLvoid*)(0));
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
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Desenarea unui disc");
	glewInit();
	Initialize();
	glutReshapeFunc(reshapeFcn);
	glutDisplayFunc(RenderFunction);
	glutCloseFunc(Cleanup);
	glutMainLoop();

}


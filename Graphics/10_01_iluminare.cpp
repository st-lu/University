// ILUMINARE
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

// identificatori 
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId,
viewLocation,
projLocation,
codColLocation,
depthLocation,
codCol;
GLint objectColorLoc, lightColorLoc, lightPosLoc, viewPosLoc;

// variabile pentru matricea de vizualizare
float Obsx = 0.0, Obsy = 0.0, Obsz = -800.f;
float Refx = 0.0f, Refy = 0.0f;
float Vx = 0.0;

// variabile pentru matricea de proiectie
float width = 800, height = 600, znear = 1, zfar = 1800, fov = 45;

// matrice utilizate
glm::mat4 view, projection;

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'l':
		Vx -= 0.1;
		break;
	case 'r':
		Vx += 0.1;
		break;
	case '+':
		Obsz += 10;
		break;
	case '-':
		Obsz -= 10;
		break;
	}
	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Obsx -= 20;
		break;
	case GLUT_KEY_RIGHT:
		Obsx += 20;
		break;
	case GLUT_KEY_UP:
		Obsy -= 20;
		break;
	case GLUT_KEY_DOWN:
		Obsy += 20;
		break;
	}
}
void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] =
	{
		// fata dinspre observator (in planul z=-50, normala este (0,0,-1))
		-50.f, -50.f, -50.f,  0.0f,  0.0f, -1.0f,
		 50.f, -50.f, -50.f,  0.0f,  0.0f, -1.0f,
		 50.f,  50.f, -50.f,  0.0f,  0.0f, -1.0f,
		 50.f,  50.f, -50.f,  0.0f,  0.0f, -1.0f,
		-50.f,  50.f, -50.f,  0.0f,  0.0f, -1.0f,
		-50.f, -50.f, -50.f,  0.0f,  0.0f, -1.0f,

		// spate (in planul z=50, normala este (0,0,1))
		-50.f, -50.f,  50.f,  0.0f,  0.0f,  1.0f,
		 50.f, -50.f,  50.f,  0.0f,  0.0f,  1.0f,
		 50.f,  50.f,  50.f,  0.0f,  0.0f,  1.0f,
		 50.f,  50.f,  50.f,  0.0f,  0.0f,  1.0f,
		-50.f,  50.f,  50.f,  0.0f,  0.0f,  1.0f,
		-50.f, -50.f,  50.f,  0.0f,  0.0f,  1.0f,

		// fata din dreapta (in planul x=-50, normala este (-1,0,0))
		-50.f,  50.f,  50.f, -1.0f,  0.0f,  0.0f,
		-50.f,  50.f, -50.f, -1.0f,  0.0f,  0.0f,
		-50.f, -50.f, -50.f, -1.0f,  0.0f,  0.0f,
		-50.f, -50.f, -50.f, -1.0f,  0.0f,  0.0f,
		-50.f, -50.f,  50.f, -1.0f,  0.0f,  0.0f,
		-50.f,  50.f,  50.f, -1.0f,  0.0f,  0.0f,

		// fata din stanga (in planul x=50, normala este (1,0,0))
		 50.f,  50.f,  50.f,  1.0f,  0.0f,  0.0f,
		 50.f,  50.f, -50.f,  1.0f,  0.0f,  0.0f,
		 50.f, -50.f, -50.f,  1.0f,  0.0f,  0.0f,
		 50.f, -50.f, -50.f,  1.0f,  0.0f,  0.0f,
		 50.f, -50.f,  50.f,  1.0f,  0.0f,  0.0f,
		 50.f,  50.f,  50.f,  1.0f,  0.0f,  0.0f,

		 // jos (in planul y=-50, normala este (0,-1,0))
		-50.f, -50.f, -50.f,  0.0f, -1.0f,  0.0f,
		 50.f, -50.f, -50.f,  0.0f, -1.0f,  0.0f,
		 50.f, -50.f,  50.f,  0.0f, -1.0f,  0.0f,
		 50.f, -50.f,  50.f,  0.0f, -1.0f,  0.0f,
		-50.f, -50.f,  50.f,  0.0f, -1.0f,  0.0f,
		-50.f, -50.f, -50.f,  0.0f, -1.0f,  0.0f,

		// sus (in planul y=50, normala este (0,1,0))
		-50.f,  50.f, -50.f,  0.0f,  1.0f,  0.0f,
		 50.f,  50.f, -50.f,  0.0f,  1.0f,  0.0f,
		 50.f,  50.f,  50.f,  0.0f,  1.0f,  0.0f,
		 50.f,  50.f,  50.f,  0.0f,  1.0f,  0.0f,
		-50.f,  50.f,  50.f,  0.0f,  1.0f,  0.0f,
		-50.f,  50.f, -50.f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VaoId);
	glGenBuffers(1, &VboId);

	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // atributul 0 = pozitie
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1); // atributul 0 = pozitie
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
void CreateShaders(void)
{
	ProgramId = LoadShaders("10_01_Shader.vert", "10_01_Shader.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
	CreateVBO();
	CreateShaders();

	// locatii ptr shader
	objectColorLoc = glGetUniformLocation(ProgramId, "objectColor");
	lightColorLoc = glGetUniformLocation(ProgramId, "lightColor");
	lightPosLoc = glGetUniformLocation(ProgramId, "lightPos");
	viewPosLoc = glGetUniformLocation(ProgramId, "viewPos");
	viewLocation = glGetUniformLocation(ProgramId, "view");
	projLocation = glGetUniformLocation(ProgramId, "projection");
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// reperul de vizualizare + matricea de proiectie
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);
	Refx = Obsx; Refy = Obsy;
	glm::vec3 PctRef = glm::vec3(Refx, Refy, 800.0f);
	glm::vec3 Vert = glm::vec3(Vx, 1.0f, 0.0f);
	view = glm::lookAt(Obs, PctRef, Vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	projection = glm::perspective(fov, GLfloat(width) / GLfloat(height), znear, zfar);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	// Variabile uniforme pentru iluminare
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.4f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, 0.f, 0.f, -200.f);
	glUniform3f(viewPosLoc, Obsx, Obsy, Obsz);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glutSwapBuffers();
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 900);
	glutCreateWindow("Utilizarea surselor de lumina");
	glewInit();
	Initialize();
	glutIdleFunc(RenderFunction);
	glutDisplayFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}


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

//////////////////////////////////////
// identificatori 
GLuint
VaoId,
VboId,
ColorBufferId,
ProgramId,
myMatrixLocation,
viewLocation,
projLocation,
matrRotlLocation,
codColLocation;

int codCol;
float PI = 3.141592;

// matrice utilizate
glm::mat4 myMatrix, matrRot;

// elemente pentru matricea de vizualizare
float Obsx = 0.0, Obsy = 0.0, Obsz = -800.f;
float Refx = 0.0f, Refy = 0.0f;
float Vx = 0.0;
glm::mat4 view;

// elemente pentru matricea de proiectie
float width = 800, height = 600, xwmin = -800.f, xwmax = 800, ywmin = -600, ywmax = 600, znear = 200, zfar = 2000, fov = 30;
glm::mat4 projection;

void displayMatrix()
{
	for (int ii = 0; ii < 4; ii++)
	{
		for (int jj = 0; jj < 4; jj++)
			cout << myMatrix[jj][ii] << "  ";
		cout << endl;
	};
	cout << "\n";
};

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'l':
		Vx += 0.1;
		break;
	case 'r':
		Vx -= 0.1;
		break;
	case '+':
		//znear += 10;
		//zfar += 10;
		Obsz += 10;
		break;
	case '-':
		//znear -= 10;
		//zfar -= 10;
		Obsz -= 10;
		break;
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) 
{
	switch (key) {
	case GLUT_KEY_LEFT:
		Obsx -= 20;
		break;
	case GLUT_KEY_RIGHT:
		Obsx += 20;
		break;
	case GLUT_KEY_UP:
		Obsy += 20;
		break;
	case GLUT_KEY_DOWN:
		Obsy -= 20;
		break;
	}
}

void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
		// cele 4 varfuri din colturi 
		-390.0f, -290.0f, 0.0f, 1.0f,
		390.0f,  -290.0f, 0.0f, 1.0f,
		390.0f, 290.0f, 0.0f, 1.0f,
		-390.0f, 290.0f, 0.0f, 1.0f,
		// varfuri pentru axe
		-400.0f, 0.0f, 0.0f, 1.0f,
		400.0f,  0.0f, 0.0f, 1.0f,
		0.0f, -300.0f, 0.0f, 1.0f,
		0.0f, 300.0f, 0.0f, 1.0f,
		// varfuri pentru dreptunghi
		-50.0f,  -50.0f, 0.0f, 1.0f,
		50.0f, -50.0f, 0.0f, 1.0f,
		50.0f,  50.0f, 0.0f, 1.0f,
		-50.0f,  50.0f, 0.0f, 1.0f,
	};

	// culorile varfurilor din colturi
	GLfloat Colors[] = {
	  1.0f, 0.0f, 0.0f, 1.0f,
	  0.0f, 1.0f, 0.0f, 1.0f,
	  0.0f, 0.0f, 1.0f, 1.0f,
	  1.0f, 0.0f, 0.0f, 1.0f,
	};

	// se creeaza un buffer nou
	glGenBuffers(1, &VboId);
	// este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// punctele sunt "copiate" in bufferul curent
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	// se activeaza lucrul cu atribute; atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// un nou buffer, pentru culoare
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	// atributul 1 =  culoare
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
	ProgramId = LoadShaders("07_01_Shader.vert", "07_01_Shader.frag");
	glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	myMatrix = glm::mat4(1.0f);
	matrRot = glm::rotate(glm::mat4(1.0f), PI / 8, glm::vec3(0.0, 0.0, 1.0));
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
	CreateVBO();
	CreateShaders();
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// pozitia observatorului
	glm::vec3 Obs = glm::vec3(Obsx, Obsy, Obsz);

	// pozitia punctului de referinta
	Refx = Obsx; Refy = Obsy;
	glm::vec3 PctRef = glm::vec3(Refx, Refy, -1.0f);

	// verticala din planul de vizualizare 
	glm::vec3 Vert = glm::vec3(Vx, 1.0f, 0.0f);

	// matricea de vizualizare
	view = glm::lookAt(Obs, PctRef, Vert);
	/* afisare matrice vizualizare
	myMatrix=view;
	displayMatrix();
	*/

	// matricea de proiectie
	projection = glm::ortho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	// projection = glm::frustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	// projection = glm::perspective(fov, GLfloat(width)/GLfloat(height), znear, zfar);

	// matrice pentru "elementele fixe" - punctele din colturi si axe
	myMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.f / GLfloat(width), 1.f / GLfloat(height), 1.0));
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// desenare puncte din colturi si axe
	codCol = 0;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 0, 4);
	glDrawArrays(GL_LINES, 4, 4);

	// matrice pentru patratul care este vazut din unghiuri diferite
	myMatrix = projection * view;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// desenare patrat
	codCol = 1;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 8, 4);

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Transformari de vizualizare si proiectie");
	glewInit();
	Initialize();
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(RenderFunction);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutCloseFunc(Cleanup);
	glutMainLoop();
}


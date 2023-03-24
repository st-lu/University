/* DESCRIERE: DREPTUNGHI CU SATELIT -- varianta cu OpenGL "nou"
	 
	- utilizeaza diverse transformari si compunerea acestora folosind biblioteca glm
	- functii de mouse
	- transmiterea unor variabile uniforme si folosirea la colorarea primitivelor

*/
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

GLuint
  VaoId,
  VboId,
  ColorBufferId,
  ProgramId,
  myMatrixLocation,
  matrScaleLocation,
  matrTranslLocation,
  matrRotlLocation,
  codColLocation;
 
glm::mat4 myMatrix, resizeMatrix, matrTransl, matrScale1, matrScale2, matrRot, matrDepl; 


int codCol;
 float PI=3.141592, angle=0;
 float tx=0; float ty=0; 
 int width=450, height=300;
 float i=0.0, alpha=0.0, beta=0.2;

 
 
void displayMatrix ( )
{
	for (int ii = 0; ii < 4; ii++)
	{
		for (int jj = 0; jj < 4; jj++)
		cout <<  myMatrix[ii][jj] << "  " ;
		cout << endl;
	};
	cout << "\n";
	
};

void miscad (void)
{
	i = i + alpha;
  if ( i > 350.0 )
	  alpha = -10.0;
  else if ( i < -350.0 )
	   alpha = 10.0;
  angle = angle - beta;

  glutPostRedisplay ( );
}

void miscas (void)
{   
	i = i + alpha;
  if ( i < -350.0 )
	  alpha = 10.0;
  else if ( i > 350.0 )
		alpha = -10.0;
  angle = angle + beta;

  glutPostRedisplay ( );
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            alpha = -10.0; glutIdleFunc(miscas);
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            alpha = 10.0; glutIdleFunc(miscad);
         break;
      default:
         break;
   }
}

void CreateVBO(void)
{
  // varfurile 
  GLfloat Vertices[] = {

	 // varfuri pentru axe
	  -450.0f, 0.0f, 0.0f, 1.0f,
      450.0f,  0.0f, 0.0f, 1.0f,
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
  // 
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
  ProgramId=LoadShaders("05_02_Shader.vert", "05_02_Shader.frag");
  glUseProgram(ProgramId);
}
 
void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}
 
void Initialize(void)
{
      glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
}
void RenderFunction(void)
{
  // TO DO: schimbati transformarile (de exemplu deplasarea are loc pe axa Oy sau pe o alta dreapta)
  resizeMatrix= glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0)); // scalam, "aducem" scena la "patratul standard" [-1,1]x[-1,1]
  matrTransl=glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0, 0.0)); // controleaza translatia de-a lungul lui Ox
  matrDepl=glm::translate(glm::mat4(1.0f), glm::vec3(0, 80.0, 0.0)); // plaseaza patratul rosu
  matrScale1=glm::scale(glm::mat4(1.0f), glm::vec3(1.1, 0.3, 0.0)); // folosita la desenarea dreptunghiului albastru
  matrScale2=glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.25, 0.0)); // folosita la desenarea patratului rosu
  matrRot=glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0)); // rotatie folosita la deplasarea patratului rosu

  glClear(GL_COLOR_BUFFER_BIT);
  CreateVBO();

  // Matricea de redimensionare (pentru elementele "fixe") 
  myMatrix=resizeMatrix;  
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  // Apelare DrawArrays
  glDrawArrays(GL_LINES, 0, 4);

  // Matricea pentru dreptunghiul albastru 
  myMatrix=resizeMatrix * matrTransl * matrScale1;   
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix"); 
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  codCol=1;
  codColLocation = glGetUniformLocation(ProgramId, "codCol");
  glUniform1i(codColLocation, codCol);
  // Apelare DrawArrays
  glDrawArrays(GL_POLYGON, 4, 4);
  
  // Matricea pentru dreptunghiul rosu 
  myMatrix=resizeMatrix *  matrTransl * matrRot * matrDepl * matrScale2;
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix"); 
  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
  codCol=2;
  codColLocation = glGetUniformLocation(ProgramId, "codCol");
  glUniform1i(codColLocation, codCol);
  glDrawArrays(GL_POLYGON, 4, 4);

  // TO DO: adaugati si alte obiecte
  glutSwapBuffers();
  glFlush ( );
}
void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}

int main(int argc, char* argv[])
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowPosition (100,100); 
  glutInitWindowSize(800,600); 
  glutCreateWindow("Compunerea transformarilor. Utilizarea mouse-ului"); 
  glewInit(); 
  Initialize( );
  glutDisplayFunc(RenderFunction);
  glutMouseFunc(mouse);
  glutCloseFunc(Cleanup);

  glutMainLoop();
  
  
}


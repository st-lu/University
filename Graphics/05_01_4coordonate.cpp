/* TRANSFORMARI. Codul sursa este adaptat dupa OpenGLBook.com
	- sunt utilizate doua VBO pentru coordonatele varfurilor
	- transformarile si operatiile cu acestea pot fi indicate fie in programul principal, fie in shader
	- sunt exemplificate scalarea si translatia
*/
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"


  
//////////////////////////////////////

GLuint
  VaoId, 
  VboId,
  ColorBufferId,
  ProgramId,
  matrLocation;
 float m[4][4];

 
 
void CreateVBO(void)
{
  // varfurile 
  GLfloat Vertices[] = {
    -100, -100, 0, 1, // primele 4 varfuri au ultima coordonata 1
    100, -100, 0, 1,
    100, 100, 0, 1,
    -100, 100, 0, 1,
    -100, -100, 0, 0.0, // varful 5 (stanga jos) are a 4a coordonata egala cu 0
    -100, -100, 0, 0.5,  // urmatoarele 4 varfuri au ultima coordonata 0.5
    100, -100, 0, 0.5,
    100, 100, 0, 0.5,
    -100, 100, 0, 0.5,
    
  };
 

  // culorile, ca atribute ale varfurilor
  GLfloat Colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
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
  ProgramId=LoadShaders("04_01_Shader.vert", "04_01_Shader.frag");
  glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}
 
void Initialize(void)
{

    m[0][0]=0.002; m[1][1]=0.002; m[2][2]=1; m[3][3]=1; // diagonala principala
	m[0][1]=0; m[0][2]=0; m[0][3]=0;
	m[1][0]=0; m[1][2]=0; m[1][3]=0;
	m[2][0]=0; m[2][1]=0; m[2][3]=0;
	m[3][0]=0; m[3][1]=0; m[3][2]=0;
 
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului

  CreateVBO();
  CreateShaders();
}
void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glUniformMatrix4fv(matrLocation, 1, GL_TRUE, &m[0][0]);
  glPointSize(20.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glDrawArrays(GL_LINE_LOOP, 0, 4);
  glDrawArrays(GL_LINE_LOOP, 5, 4);
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
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition (100,100); // pozitia initiala a ferestrei
  glutInitWindowSize(600,600); //dimensiunile ferestrei
  glutCreateWindow("Coordonate omogene. Transformari si matrice"); // titlul ferestrei
  glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
  Initialize( );
  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);
  glutMainLoop();

}


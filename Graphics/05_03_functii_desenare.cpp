 /* FUNCTII DE DESENARE
 Elemente de noutate:
	- folosirea indecsilor: elemente asociate (matrice, buffer)
	- cele 4 functii de desenare (glDrawArrays, glDrawElements, glDrawElementsBaseVertex, glDrawArraysInstanced) */
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
  EboId,
  ColorBufferId,
  ProgramId,
  myMatrixLocation,
  codColLocation;
 

glm::mat4 myMatrix, resizeMatrix, matrTransl; 


int codCol;
 float PI=3.141592, angle=0;
 float tx=0; float ty=0; 
float width=90.f, height=90.f;
 float i=0.0, alpha=0.0, beta=0.2;



void CreateVBO(void)
{
 
	// coordonatele varfurilor
    static const GLfloat vf_pos[] =
	{
	-10.0f, -10.0f, 0.0f, 1.0f,
	10.0f, -10.0f, 0.0f, 1.0f,
	-10.0f, 10.0f, 0.0f, 1.0f,
	-10.0f, -10.0f, 0.0f, 1.0f,
	};  
	// culorile varfurilor
	static const GLfloat vf_col[] =
	{
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f
	};
	// indici pentru trasarea unui triunghi
	static const GLuint vf_ind[] =
	{
	0, 1, 2
	};
 

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
   glBufferData(GL_ARRAY_BUFFER, sizeof(vf_col)+sizeof(vf_pos), NULL, GL_STATIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vf_pos), vf_pos);
   glBufferSubData(GL_ARRAY_BUFFER, sizeof(vf_pos), sizeof(vf_col),vf_col);
 
    // buffer-ul pentru indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vf_ind), vf_ind, GL_STATIC_DRAW);
 
    // se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vf_pos));
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
  ProgramId=LoadShaders("05_03_Shader.vert", "05_03_Shader.frag");
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

  resizeMatrix= glm::ortho(-width, width, -height, height);

  glClear(GL_COLOR_BUFFER_BIT);

  // creare VBO
  CreateVBO();
  // Creare shader + transmitere variabile uniforme
  CreateShaders();
  myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

 
  // Desenare cu glDrawArrays
	  // Matricea de redimensionare
	  myMatrix=resizeMatrix;  
	  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
	  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Utilizarea indicilor
	  // Matricea: redimensionare+translatie
	  myMatrix=resizeMatrix*glm::translate(glm::mat4(1.0f), glm::vec3(-20.0, -20.0, 0.0));  
	  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
	  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	 
// Utilizarea indicilor
     // Matricea: redimensionare+ alta translatie (pe verticala)
	  myMatrix=resizeMatrix*glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 40.0, 0.0));  
	  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
	  glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL, 1);

// Randare instantiata
	// Matricea: redimensionare+ alta translatie (pe orizontala)
	  myMatrix=resizeMatrix*glm::translate(glm::mat4(1.0f), glm::vec3(70.0, 0.0, 0.0));  
	  glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);
	  glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

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
  glutInitWindowPosition (100,100); 
  glutInitWindowSize(800,600); 
  glutCreateWindow("Buffere. Functii de desenare"); 
  glewInit(); 
  Initialize( );
  glutDisplayFunc(RenderFunction);
  glutCloseFunc(Cleanup);

  glutMainLoop();
  
  
}


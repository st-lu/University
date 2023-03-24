/* INDEXARE
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
myMatrixLocation;


float width = 80.f, height = 60.f;
glm::mat4 myMatrix, resizeMatrix=glm::ortho(-width, width, -height, height);

void CreateVBO(void)
{
    // coordonatele varfurilor
    static const GLfloat vf_pos[] =
    {
    -5.0f, -5.0f, 0.0f, 1.0f,
     5.0f,  -5.0f, 0.0f, 1.0f,
     5.0f,  5.0f, 0.0f, 1.0f,
    -5.0f,  5.0f, 0.0f, 1.0f,
 
    };
    // culorile varfurilor
    static const GLfloat vf_col[] =
    {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    };
    // indici pentru trasarea unui triunghi
    static const GLuint vf_ind[] =
    {
    0, 1, 2, 2, 3, 0
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vf_col) + sizeof(vf_pos), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vf_pos), vf_pos);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vf_pos), sizeof(vf_col), vf_col);

    // buffer-ul pentru indici
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vf_ind), vf_ind, GL_STATIC_DRAW);

    // se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vf_pos));
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
    ProgramId = LoadShaders("06_02_Shader.vert", "06_02_Shader.frag");
    glUseProgram(ProgramId);
}

void DestroyShaders(void)
{
    glDeleteProgram(ProgramId);
}

void Initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
    CreateShaders();
}
void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Creare VBO
    CreateVBO();
    // Transmitere variabile uniforme
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
    // Desenare
    myMatrix = resizeMatrix;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));
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
    glutInitWindowSize(800, 600);
    glutCreateWindow("Utilizarea indexarii varfurilor");
    glewInit();
    Initialize();
    glutDisplayFunc(RenderFunction);
    glutCloseFunc(Cleanup);

    glutMainLoop();


}


 /* ELEMENTE DE NOUTATE:
- GL_QUADS ca mod de trasare a primitivelor
- functii specifice OpenGL "vechi": 
	gluLookAt
	glOrtho
	glMatrixMode
	// sunt generate transformari pentru vizualizare 3D
	glPolygonMode
- functia "reshape" pentru a pastra proportiile desenului
*/


#include <windows.h>
#include <GL/freeglut.h>

GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 0.0, y0 = 0.0, z0 = 0.0;
GLfloat xref = 0.0, yref = 0.0, zref = 40.0;
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;

GLfloat xwMin = -20.0, ywMin = -20.0, xwMax = 20.0, ywMax = 20.0;

GLfloat dnear = 0.0, dfar = 60.0;

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);

	glMatrixMode (GL_MODELVIEW);
	gluLookAt (x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode (GL_PROJECTION);
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void desen1 (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

 
	glLineWidth (4.0);
	 glPolygonMode (GL_FRONT, GL_FILL);
     glPolygonMode (GL_BACK, GL_LINE);
	 glBegin (GL_QUADS);
	    glColor3f (1.0, 0.0, 0.0);
		glVertex3i (5, -5, 5);
		glVertex3i (-5, -5, 5);
		glVertex3i (-5, 5, 5);
		glVertex3i (5, 5, 5);
		glColor3f (0.0, 0.0, 0.5);
		glVertex3i (3, 3, 10);
		glVertex3i (-3, 3, 10);
		glVertex3i (-3, -3, 10);
		glVertex3i (3, -3, 10);
 
	glEnd ( );

	glFlush ( );
}

void desen2 (void) //elimina poligoanele care sunt vazute din spate sau fata cu glCull
{
	glClear (GL_COLOR_BUFFER_BIT);

 
	 glPolygonMode (GL_FRONT, GL_FILL);
	 glPolygonMode (GL_BACK, GL_LINE);
     glEnable (GL_CULL_FACE);
	 glCullFace (GL_FRONT);
	 glBegin (GL_QUADS);
		 glColor3f(1.0, 0.0, 0.0);
		 glVertex3i(5, -5, 5);
		 glVertex3i(-5, -5, 5);
		 glVertex3i(-5, 5, 5);
		 glVertex3i(5, 5, 5);
		 glColor3f(0.0, 0.0, 0.5);
		 glVertex3i(3, 3, 10);
		 glVertex3i(-3, 3, 10);
		 glVertex3i(-3, -3, 10);
		 glVertex3i(3, -3, 10);
	glEnd ( );
	glDisable (GL_CULL_FACE);
	glFlush ( );
}

void reshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, newWidth,newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}
void main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Poligoane 3D");

	init ( );
	glutDisplayFunc (desen2);
	glutReshapeFunc (reshapeFcn);
	glutMainLoop ( );
}


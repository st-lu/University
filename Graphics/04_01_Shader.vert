// Shader-ul de varfuri  
 
 #version 400


in vec4 in_Position;
in vec4 in_Color;

out vec4 gl_Position; 
out vec4 ex_Color;
uniform mat4 m;


void main(void)
  {
  /*
   // aplicarea unei translatii
   vec4 vect;
   vect=vec4(0.3, 0.0, 0.0, 0.0); 
   gl_Position=in_Position+vect;
    
 */


 /*  // Rescalare. Var 1. Matricea de transformare (scalare) este indicata in shader
    mat4 matr;  
	matr[0][0]=0.01; matr[1][1]=0.1; matr[2][2]=1; matr[3][3]=1; // diagonala principala
	matr[0][1]=0; matr[0][2]=0; matr[0][3]=0;
	matr[1][0]=0; matr[1][2]=0; matr[1][3]=0;
	matr[2][0]=0; matr[2][1]=0; matr[2][3]=0;
	matr[3][0]=0; matr[3][1]=0; matr[3][2]=0;
	gl_Position = matr*in_Position;
	*/ 
 


 // Rescalare. Var 2. Folosirea variabilelor uniforme 

      // gl_Position = m*in_Position;
   

     gl_Position=in_Position;
 
    ex_Color = in_Color;
   } 
 
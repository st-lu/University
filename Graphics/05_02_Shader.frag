
// Shader-ul de fragment / Fragment shader  
 
 #version 400

in vec4 ex_Color;
uniform int codCol;
 
out vec4 out_Color;

void main(void)
  {
	if ( codCol==0 )
		out_Color = ex_Color;
	if ( codCol==1 )
		out_Color=vec4 (0.0, 0.0, 1.0, 0.0);
	if ( codCol==2 )
		out_Color=vec4 (1.0, 0.0, 0.0, 0.0);

  }
 
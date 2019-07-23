#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float x_pos = 0;
float y_pos = 0;
float z_pos = 0;
float theta = M_PI/6;
float phi  = M_PI/2;
float R = 9;

void changeSize(int w, int h)
{
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(90,ratio,1,1000);
}

void display()
{
	x_pos = R * cos(phi)*cos(theta);
	y_pos = R * sin(theta);
	z_pos = R * sin(phi)*cos(theta);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPushMatrix();
	if (cos(theta)>=0) gluLookAt(x_pos, y_pos, z_pos, 0, 0, 0, 0, 1, 0);
	else gluLookAt(x_pos, y_pos, z_pos, 0, 0, 0, 0, -1, 0);
	
	///////////////////////////////////////////////////////////////////////////////////////////
    //Set the ambient light to the previously defined light_ambient vector (whose parameters are the RGBA values of teh light)
    GLfloat	light_ambient[] = {1, 1, 1, 1}; //White ambient light
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	
	//Set the position of the light source
	GLfloat light_position[] = {0, 5, 7, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	//Enable the diffusion and specular lights
	GLfloat white_light[] = {0.5,0.5,0.5,1};
	GLfloat red_light[] = {0.5, 0.0, 0.0, 1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    //Set Material Properties
	GLfloat mat_specular[] = {1, 1, 1, 1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //During specular reflection, how much Red, Green and Blue will be scattered
	GLfloat mat_shininess[] = {50};
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //Specular coefficient
	GLfloat black[] = {0, 0, 0};
	glMaterialfv(GL_FRONT,GL_AMBIENT, black); //Basically - Material color
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	
	//Draw the spheres
    glPushMatrix();
	glTranslatef(0, 4, -8);
	glutSolidSphere(3, 50, 50);
	glPopMatrix();

    glPushMatrix();
	glTranslatef(0, -2, -4);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

    glPushMatrix();
	glTranslatef(0, 0, 2);
	glutSolidSphere(3, 50, 50);
	glPopMatrix();
    
    /*
    glPushMatrix();
	glTranslatef(0, 0, 2);
	glutWireTorus(1, 3, 100, 100);
	glPopMatrix();
     */
	
	
	glPopMatrix();

	glutSwapBuffers();
}

void processKeys(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w': theta += 0.1;break;
	case 's': theta -= 0.1; break;
	case 'a': phi += 0.1; break;
	case 'd': phi -= 0.1; break;
	case 't': if (R >= 8) R -= 0.5; break;
	case 'g': if (R<100) R += 0.5; break;
	case 27: exit(0); break;
	}
	glutPostRedisplay();
}

void init()
{

	glClearColor(0, 0, 0, 0);

    ///////////////////////////////////////////////////////////////////////
    /*
    GL_FLAT colors the interior of a polygon with the solid color that was current when the polygon's last vertex was specified.
    GL_SMOOTH does shading calculations in the interior of the triangle, it interpolates the vertex colors and smoothly transitions
    from one to another.
    */
	glShadeModel(GL_SMOOTH);
	//Tell OpenGL to use lightning calculations.
	glEnable(GL_LIGHTING);
	//Enable the light source
	glEnable(GL_LIGHT0);
	///////////////////////////////////////////////////////////////////////
	
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(90, 1, 1, 1000);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);

	int window;
	window = glutCreateWindow("Spheres");
	init();

	glutReshapeFunc(changeSize);
	glutDisplayFunc(display);
	glutKeyboardFunc(processKeys);
	glutMainLoop();

	return 0;
}


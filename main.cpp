#include <stdlib.h>
#include <stdio.h>
#include "GL/freeglut.h"

// constants
#include "constants.h"

// event callbacks
#include "callbacks.h"

void initRendering()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_X, SCREEN_Y, 0, 5, -5);
	glMatrixMode(GL_MODELVIEW);

	glPointSize(4);
	glLineWidth(1);

}


int main( int argc, char** argv )
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );

	glutInitWindowPosition( 20, 60 );
	glutInitWindowSize( SCREEN_X, SCREEN_Y );
	glutCreateWindow( TITLE_STRING );

	initRendering();

	glutKeyboardFunc( KeyboardDownCallback );
	glutKeyboardUpFunc( KeyboardUpCallback );			
	glutMouseFunc(MouseCallback);
	glutReshapeFunc( WindowResizeCallback );
	glutDisplayFunc( SceneDisplayCallback );
	
	glutMainLoop(  );
		
	return(0);
}


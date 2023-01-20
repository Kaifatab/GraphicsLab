/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
  float x = 0.0,y=0.0,r=100.0;
  // Set every pixel in the frame buffer to the current clear color.
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 0, 0);

  glBegin(GL_POINTS);
  glVertex3f(300.0,200.0,0.0);
  for(int i=0;i<1000;i++)
  {
      y = sqrt((r*r)-(x*x));
      glVertex3f(x+250.0,y+250.0,0.0);
      glVertex3f(-x+250.0,y+250.0,0.0);
      glVertex3f(x+250.0,-y+250.0,0.0);
      glVertex3f(-x+250.0,-y+250.0,0.0);
      x = x+1;
  }

  glEnd();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  glFlush();
}


void init()
{
   glClearColor(0.0,0.0,0.0,0.7);
   glMatrixMode(GL_PROJECTION);
   glOrtho(0.0,500.0,0.0,500.0,-10.0,10.0);
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(250,250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Circle");

    init();
    glutDisplayFunc(display);


    glutMainLoop();

    return EXIT_SUCCESS;
}

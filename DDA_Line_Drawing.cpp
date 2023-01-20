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
#include<bits/stdc++.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

using namespace std;

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


void dda(int x1, int x2, int y1, int y2) {

  float dx = x2 - x1;
  float dy = y2 - y1;
  // cout << dy << " " << dx << endl;
  int step = abs(dx) > abs(dy) ? dx : dy;
  cout << step << endl;
  float x = x1;
  float y = y1;
  for (int i = 1; i <= step; i++) {
    cout << x << " " << y << endl;
    glVertex3f(x, y, 0);
    x += (dx / step);
    y += (dy / step);
  }
}


static void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(2.0);
  glBegin(GL_POINTS);
  int x1, x2, y1, y2;
  //cin >> x1 >> x2 >> y1 >> y2;
  x1 = -3;
  x2 = -5;
  y1 = 8;
  y2 = 15;
  dda(x1, x2, y1, y2);

  glEnd();
  glFlush();
}


void init()
{
   glClearColor(0.0,0.0,0.0,0.7);
   glMatrixMode(GL_PROJECTION);
   glOrtho(-20.0,20.0,-20.0,20.0,-10.0,10.0);
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(250,250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("DDA Algorithm");

    init();
    glutDisplayFunc(display);


    glutMainLoop();

    return 0;
}

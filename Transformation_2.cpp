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
#include <GL/gl.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

int click_right=0, click_left=0;
int previous_click = -1;
int dx = 0, dy = 0, dz = 0;
float theta = 0;

float px1 = 4, py1 = 8.5, px2 = 1, py2 = 7, px3 = 4, py3 = 10, px4 = 7, py4=7;
float cx = 4;
float cy = 8.5;


void transformation() {
  // cout << cx << " " << cy << endl;
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);



  glBegin(GL_LINE_LOOP);

  glVertex3f((px1-cx)*cos(theta*(3.1415/180)) - (py1-cy)*sin(theta*(3.1415/180)) + dx,
             (px1-cx)*sin(theta*(3.1415/180)) + (py1-cy)*cos(theta*(3.1415/180)) + dy,
             0);

  glVertex3f((px2-cx)*cos(theta*(3.1415/180)) - (py2-cy)*sin(theta*(3.1415/180)) + dx,
             (px2-cx)*sin(theta*(3.1415/180)) + (py2-cy)*cos(theta*(3.1415/180)) + dy,
             0);

  glVertex3f((px3-cx)*cos(theta*(3.1415/180)) - (py3-cy)*sin(theta*(3.1415/180)) + dx,
             (px3-cx)*sin(theta*(3.1415/180)) + (py3-cy)*cos(theta*(3.1415/180)) + dy,
             0);

  glVertex3f((px4-cx)*cos(theta*(3.1415/180)) - (py4-cy)*sin(theta*(3.1415/180)) + dx,
             (px4-cx)*sin(theta*(3.1415/180)) + (py4-cy)*cos(theta*(3.1415/180)) + dy,
             0);

  glEnd(); // End quadrilateral coordinates

  glFlush();
  glutPostRedisplay();
  glutSwapBuffers();
}

void scaling() {}

void display(void) {
  transformation();
  //glBegin(GL_POINTS);
  //glVertex3f(0, 0, 0);
  //glEnd();
  //glFlush();
}

void key(int key, int x, int y) {

  switch (key) {
  case GLUT_KEY_UP:
    //px1 = 4, py1 = 8.5, px2 = 1, py2 = 7, px3 = 4, py3 = 10, px4 = 7, py4=7;
    if(previous_click==-1 || previous_click==1)
        dy++;
    if(previous_click==3)
        theta += 180;
    if(previous_click==2)
        theta += 90;
    if(previous_click==4)
        theta -= 90;
    previous_click = 1;
    glutPostRedisplay();
    break;

  case GLUT_KEY_DOWN:
    //px1 = 4, py1 = 8.5, px2 = 1, py2 = 7, px3 = 4, py3 = 10, px4 = 7, py4=7;
    if(previous_click==-1 || previous_click==1)
        theta += 180;
    if(previous_click==3)
        dy--;
    if(previous_click==2)
        theta -= 90;
    if(previous_click==4)
        theta += 90;
    previous_click = 3;
    glutPostRedisplay();
    break;

  case GLUT_KEY_RIGHT:
    //px1 = 4, py1 = 8.5, px2 = 1, py2 = 7, px3 = 4, py3 = 10, px4 = 7, py4=7;
    if(previous_click==-1 || previous_click==1)
        theta -= 90;
    if(previous_click==3)
        theta += 90;
    if(previous_click==2)
        dx++;
    if(previous_click==4)
        theta -= 180;
    previous_click = 2;
    glutPostRedisplay();
    break;

  case GLUT_KEY_LEFT:
    //px1 = 4, py1 = 8.5, px2 = 1, py2 = 7, px3 = 4, py3 = 10, px4 = 7, py4=7;
    if(previous_click==-1 || previous_click==1)
        theta += 90;
    if(previous_click==3)
        theta -= 90;
    if(previous_click==2)
        theta += 180;
    if(previous_click==4)
        dx--;
    previous_click = 4;
    glutPostRedisplay();
    break;
  }
}

/* Program entry point */

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glPointSize(5);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50, 50, -50, 50, -10.0, 10.0);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Demo");
  init();
  glutDisplayFunc(display);
  glutSpecialFunc(key);
  glutMainLoop();
  return 0;
}

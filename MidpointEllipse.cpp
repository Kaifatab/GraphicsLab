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
#include<cmath>


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

// Center of the ellipse = (320, 240)
float h = -9, k = 9;


void plot_point (int x , int y) {
    float rotated_x = x * 0.7071 - y * 0.7071;
    float rotated_y = x * 0.7071 + y * 0.7071;
    glVertex3f(rotated_x + h , rotated_y + k , 0.0);

    cout<<rotated_x + h<<" "<<rotated_y + k<<endl;
}



void ellipse(int a, int b)
{
    float x = 0, y = b, theta = (3.1416*90)/180, alpha = (3.1416*45)/180;
    //cout<<x<<" "<<y<<endl;
    //glVertex3f(x,y,0);


    float p1 = b*b - (a*a)*b + (a*a)*(0.25) ;
    //slope
    float dx = 2*(b*b)*x;
    float dy = 2*(a*a)*y;

    glVertex2i(0,0);
    glVertex2i(-9,9);

    while(abs(dx) < abs(dy))
    {
         plot_point(x , y);
        plot_point(-x , y);
        plot_point(x , -y);
        plot_point(-x, -y);

         x++;
         dx = dx + 2*(b*b);

         if(p1 < 0)
         {
            p1 = p1 + dx + (b*b);
         }
         else
         {
            y = y - 1;
            dy = dy - 2*(a*a);
            p1 = p1 + dx - dy + (b*b);
         }
    }


    // 2nd part
    float p2 = (b*b)*(x+0.5)*(x+0.5) + (a*a)*(y-1)*(y-1) - (a*a)*(b*b) ;

    while(y>=0)
    {
         plot_point(x , y);
        plot_point(-x , y);
        plot_point(x , -y);
        plot_point(-x, -y);
         y--;
         dy = dy - 2*(a*a);

        if(p2>=0)
        {
            x = x;
            p2 = p2 - dy + (a*a);
        }
        else
        {
            x = x + 1;
            dx = dx + 2*(b*b);
            p2 = p2 + dx - dy + (a*a);
        }
    }

}


static void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(2.0);
  int a = 10;
  int b = 5;
  glBegin(GL_POINTS);
  ellipse(a,b);
  glEnd();
  glFlush();
}


void init()
{
   glClearColor(0.0,0.0,0.0,0.7);
   glMatrixMode(GL_PROJECTION);
   glOrtho(-50.0,50.0,-50.0,50.0,-10.0,10.0);
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(250,250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Midpoint Ellipse Algorithm");

    init();
    glutDisplayFunc(display);


    glutMainLoop();

    return 0;
}

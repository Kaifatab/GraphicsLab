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
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#include <stdlib.h>

using namespace std;

int screenheight = 600;
 int screenwidth = 800;
 bool flag = true;


float xmin=0, ymin=0, xmax=7, ymax=6;
int n;
float points[500][4];

void DrawRect(float x0, float y0, float  x1, float y1)
 {
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3d(1,1,1);
      glBegin(GL_LINE_LOOP);
           glVertex2f(x0,y0);
           glVertex2f(x0,y1);
           glVertex2f(x1,y1);
           glVertex2f(x1,y0);
      glEnd();
      glFlush();
 }

void DrawLine(float x0, float y0, float x1, float y1){
      glColor3d(1,0,0);
      glBegin(GL_LINES);
           glVertex2f(x0,y0);
           glVertex2f(x1,y1);
      glEnd();
      glFlush();
 }



 const int INSIDE = 0;   /// 0000
 const int BOTTOM = 1;   /// 0001
 const int RIGHT  = 2;   /// 0010
 const int TOP    = 4;   /// 0100
 const int LEFT   = 8;   /// 1000

 //const double tol = 0.0000001;

int CompCode(float x, float y)
 {
      int code;

      code = INSIDE;
      if (x <= xmin)
           code |= LEFT;
      else if (x >= xmax )
           code |= RIGHT;
      else if (y <= ymin)
           code |= BOTTOM;
      else if (y >= ymax)
           code |= TOP;

      return(code);
 }

 void lineclip(float x0,float y0,float x1,float y1) {
      int code0,code1;
      float midx,midy;

      if(abs(x0-x1)<=0.1 && abs(y0-y1)<=0.1) ///when to stop the iteration
           return;

      code0=CompCode(x0,y0);
      code1=CompCode(x1,y1);

 // cout<<code0<<" "<<code1<<endl;

      if( !(code0 | code1) ) { ///if bitwise OR is 0, completely inside the window
          DrawLine(x0,y0,x1,y1);
          return;
      }

      else if(code0 & code1) ///if bitwise AND is not 0, completely outside the window
           return ;

      midx=(x0+x1)/2.0;  ///calculate the midpoint
      midy=(y0+y1)/2.0;


      lineclip(midx,midy,x1,y1); ///recusion on the new segments
      lineclip(x0,y0,midx,midy);
 }


static void display(void)
{
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //black
      glClear(GL_COLOR_BUFFER_BIT);

      DrawRect(xmin,ymin,xmax,ymax);

      lineclip(points[0][0],points[0][1],points[0][2],points[0][3]);
      lineclip(points[1][0],points[1][1],points[1][2],points[1][3]);
      lineclip(points[2][0],points[2][1],points[2][2],points[2][3]);
      lineclip(points[3][0],points[3][1],points[3][2],points[3][3]);
      lineclip(points[4][0],points[4][1],points[4][2],points[4][3]);

      glFlush();
}



/* Program entry point */

int main(int argc, char *argv[])
{

      float x1,x2,y1,y2;

      //cout<<"Enter the window points: ";
      cin >> xmin >> ymin;

      //cout<<"Enter lower right corner of the window: ";
      cin >> xmax >> ymin;

      //cout<<"Enter upper right corner of the window: ";
      cin >> xmax >> ymax;

      //cout<<"Enter upper left corner of the window: ";
      cin >> xmin >> ymax;


      //cout<<"Enter the no of lines: ";
      cin>>n;

      for(int i=0; i<n; i++)
      {
          //cout<<"Enter two endpoints: ";
          cin>> x1 >> y1 >> x2 >> y2;
          points[i][0] = x1;
          points[i][1] = y1;
          points[i][2] = x2;
          points[i][3] = y2;
      }


    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");


    glutDisplayFunc(display);

    glClearColor(1,1,1,1);

    glLoadIdentity();
    gluOrtho2D( -10.0, 20.0, -10.0, 20.0 );

    glutMainLoop();

    return 0;
}

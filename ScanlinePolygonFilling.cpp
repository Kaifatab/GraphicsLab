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
#include<bits/stdc++.h>
#include <stdlib.h>

using namespace std;


struct edge{
  double ymin;
  double x;///x for ymin
  double ymax;
  double m;
};

vector<edge>Elist;
struct edge E;


bool compare(edge a,edge b)
{
    return a.ymin<b.ymin;
}


void prep(double x1, double y1, double x2, double y2)
{
    /**
    to ensure we are going from bottom to top
    ensure y1<y2
    if y1>y2 swap the points
    */
    if(y1>y2)
    {
        int t;

        t = y1;
        y1 = y2;
        y2 = t;

        t = x1;
        x1 = x2;
        x2 = t;
    }

    E.ymin = y1;
    E.ymax = y2;
    E.x = x1;

    /**inverse of the slope of the line*/
    //cout<<x1<<" "<<x2<<"    "<<y1<<" "<<y2<<endl;
    if((y2-y1)==0)
        E.m = (x2-x1)*1.0;
    else
        E.m = (x2-x1)*1.0/(y2-y1)*1.0;
    //cout<<E.m<<endl;

    Elist.push_back(E);
}

void scanline()
{
    sort(Elist.begin(),Elist.end(),compare);

    int y = Elist[0].ymin;
    while(y <= 10)
    {
        vector<double>X;

        for(int i=0; i<Elist.size(); i++)
        {
            if((y>=Elist[i].ymin) && (y<=Elist[i].ymax))
            {
                cout<<Elist[i].m<<" "<<Elist[i].x<<endl;
                X.push_back(Elist[i].x);
                Elist[i].x += Elist[i].m;
            }
        }

        y++;

        sort(X.begin(),X.end());

        for(int i=0; i<X.size(); i+=2)
        {
            //cout<<X[i]<<" "<<X[i+1]<<" "<<y<<endl;
            glBegin(GL_LINES);
            glVertex3f(X[i],y-1,0);
            glVertex3f(X[i+1],y-1,0);
            glEnd();
            glFlush();
        }
    }
}

static void display(void)
{
    //Points
    int p1[2] = {0,-4};
    int p2[2] = {-4,-2};
    int p3[2] = {-4,0};
    int p4[2] = {-2,2};
    int p5[2] = {0,0};
    int p6[2] = {4,4};
    int p7[2] = {4,-4};


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glPointSize(2.0);


    /**
    glBegin(GL_LINES);
    glVertex2i(-4,0);
    glVertex2i(0,0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(-4,-2);
    glVertex2i(0,-2);
    glEnd();
    */




    //drawing polygon

    glBegin(GL_LINE_LOOP);
      glVertex2iv(p1);
      glVertex2iv(p2);
      glVertex2iv(p3);
      glVertex2iv(p4);
      glVertex2iv(p5);
      glVertex2iv(p6);
      glVertex2iv(p7);
    glEnd();
    glFlush();


    /** ploting the points for checking
    //glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
      glVertex2i(0,0);
      glVertex2i(-4,2);
      glVertex2i(-2,6);
      glVertex2i(1,3);
      glVertex2i(4,4);
      glVertex2i(6,2);
      glVertex2i(6,0);

    glEnd();
    **/


    prep(p1[0],p1[1],p2[0],p2[1]);
    prep(p2[0],p2[1],p3[0],p3[1]);
    prep(p3[0],p3[1],p4[0],p4[1]);
    prep(p4[0],p4[1],p5[0],p5[1]);
    prep(p5[0],p5[1],p6[0],p6[1]);
    prep(p6[0],p6[1],p7[0],p7[1]);
    prep(p7[0],p7[1],p1[0],p1[1]);

    scanline();

}


void init()
{
   glClearColor(0.0,0.0,0.0,0.7);
   glMatrixMode(GL_PROJECTION);
   glOrtho(-10.0,10.0,-10.0,10.0,-10.0,10.0);
   glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Scanline Polygon fill");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

#include<windows.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#include<math.h>
#include <stdlib.h>
using namespace std;

int color[10][20];
void flood(int x,int y)
{
    if(color[x][y] == -1)
    {
        color[x][y]=1;
        glColor3f(1.0,1.0,0.0);
        glVertex3f(x,x+y,0.0);

        flood(x+1,y);
        flood(x,y+1);
        flood(x-1,y);
        flood(x,y-1);
        flood(x-1,y-1);
        flood(x-1,y+1);
        flood(x+1,y-1);
        flood(x+1,y+1);

    }
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POINTS);
    for(int i=1; i<=5; i++)
    {
        for(int j=1; j<=10; j++)
        {
            color[i][i+j] = -1;
            //glVertex3f(i,i+j,0.0);
        }
    }
    flood(2,3);
    glEnd();
    glFlush();

}

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0,20.0,-20.0,20.0,-10.0,10.0);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1024,1024);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Demo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();


    return 0;
}

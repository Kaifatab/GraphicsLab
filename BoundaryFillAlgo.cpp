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

vector<int>V;


void init(){
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-20.0,20.0,-20.0,20.0,0.0,0.0);
}

void bound(int x, int y, float* fc, float* bc){
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(
     color[0]!=fc[0] || color[1]!=fc[1] || color[2]!=fc[2])){
        glColor3f(fc[0],fc[1],fc[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
        bound(x+1,y,fc,bc);
        bound(x-2,y,fc,bc);
        bound(x,y+2,fc,bc);
        bound(x,y-2,fc,bc);
    }
}


void world(){
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glBegin(GL_POINTS);

    for( int i=1; i<=5; i++)
    {
        for(int j=1; j<=10; j++)
        {
            if(i==1 || i==5)
            {
                glVertex2i(i,i+j);
            }
            if(j==1 || j==10)
            {
                glVertex2i(i,i+j);
            }
        }
    }
    glEnd();
    glFlush();

    /**
    glBegin(GL_LINE_LOOP);
        glVertex2i(150,100);
        glVertex2i(300,300);
        glVertex2i(450,100);
    glEnd();
    */


    float backgroundColor[] = {1,0,0};
    float fillColor[] = {0,0,1};
    //bound(2,7,fillColor,backgroundColor);

    //glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Boundary fill algorithm");
    glutDisplayFunc(world);

    init();
    glutMainLoop();
    return 0;
}

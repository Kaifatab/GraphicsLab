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

#include <stdlib.h>

float x_min=-0.5, x_max=0.5, y_min=-0.5, y_max=0.5;
float x1=-0.7, y1=-0.3, x2=0.6, y2=0.9;

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

int c1,c2;
int left=1, right=2, bot=3, top=4;
int Clip_Flag = 0;

int get_code(float x, float y)
{
    int code = 0;

    if(x<x_min)
      code = code | left;

    if(x>x_max)
      code = code | right;

    if(y<y_min)
      code = code | bot;

    if(y>y_max)
      code = code | top;

    return code;
}


void Clip()
{
    int c,x,y;

    if(c1)
      c = c1;
    else
      c = c2;

    if(c & left)
    {
        x = x_min;
        y = y1 + (y2-y1)* ((x_min-x1)/(x2-x1));
    }
    if(c & right)
    {
        x = x_max;
        y = y1 + (y2-y1)* ((x_max-x1)/(x2-x1));
    }
    if(c & bot)
    {
        y = y_min;
        x = x1 + (x2-x1)* ((y_min-y1)/(y2-y1));
    }
    if(c & top)
    {
        y = y_max;
        x = x1 + (x2-x1)* ((y_max-y1)/(y2-y1));
    }

    if(c==c1)
    {
        x1=x;
        y1=y;
    }
    else
    {
        x2=x;
        y2=y;
    }
}


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Define the window
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
      glVertex2f(x_min,y_min);
      glVertex2f(x_max,y_min);
      glVertex2f(x_max,y_max);
      glVertex2f(x_min,y_max);
    glEnd();

    //Define the lines
    glColor3f(1,0,0);
    glBegin(GL_LINES);
      glVertex2f(x1,y1);
      glVertex2f(x2,y2);
    glEnd();

    while(1 & Clip_Flag==1)
    {
        c1 = get_code(x1,y1);
        c2 = get_code(x2,y2);

        if( (c1|c2)==0 )
          break;
        else if( (c1&c2)!=0)
          break;
        else
          Clip();
    }


    glFlush();
}


void Key(unsigned char ch, int x, int y)
{
    Clip_Flag = 1;
    glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Cohen Sutherland Algorithm");

    glutDisplayFunc(display);
    glutKeyboardFunc(Key);
    glutMainLoop();

    return 0;
}

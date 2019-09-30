//#ingure -clude <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

double scale = 1;
double scalex = 1;
double scaley = 1;
bool reflectX = 0;
bool reflectY = 0;
double offsetX = 0;
double offsetY = 0;
double rot = 0;

void handle_key(unsigned char key, int mousex, int mousey)
{
    switch (key)
    {
    case 'a':
    case 'A':
        scalex *= 1.1;
        scaley *= 1.1;
        break;
    case 'd':
    case 'D':
        scalex /= 1.1;
        scaley /= 1.1;
        break;
    case 'x':
    case 'X':
        scalex *= 1;
        scaley *= -1;
        // cout << "haha" << endl;
        break;
    }

    glutPostRedisplay();
}

void display(void)
{
    /*  clear all pixels  */
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Desenha Eixos
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glVertex2f(0, -100);
    glVertex2f(0, 100);
    glEnd();

    // glTranslatef(25, 35, 0);
    glScalef(scalex, scaley, 0);
    glTranslatef(25, 25, 0);

    glPointSize(5.0);
    glPolygonMode(GL_FRONT, GL_FILL);

    glLineWidth(3); // Determina a espessura da linha que ser� desenhada

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-25, -25);
    glVertex2f(25, -25);
    glVertex2f(25, 0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0, 0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0, 25);
    glVertex2f(-25, 25);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);
    glVertex2f(30.0, 40.0);
    glEnd();

    glFlush();
}

void init(void)
{
    /*  select clearing (background) color       */
    glClearColor(1.0, 1.0, 1.0, 1.0);

    /*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformacoes 2D");
    init();
    glutKeyboardFunc(handle_key);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0; /* ISO C requires main to return int. */
}

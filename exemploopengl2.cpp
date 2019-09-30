//#ingure -clude <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

void display(void)
{
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Desenha Eixos
    glLineWidth(1);
        glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(100,0);
        glVertex2f(-100,0);
        glVertex2f(0,100);
        glVertex2f(0,-100);
    glEnd();

    //Aplique transformações aqui...

    glRotatef(90,0,0,1);
    // glTranslatef()

	glColor3f (1.0, 0.0, 0.0);
    glPointSize (5.0);
    glPolygonMode (GL_FRONT, GL_FILL);


    //Desenha casa
    glLineWidth(3); // Determina a espessura da linha que ser� desenhada
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(30.0,60.0);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(70.0,60.0);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(50.0,72.00);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2f(70.0,60.0);
        glVertex2f(30.0,60.0);
        glVertex2f(30.0,40.0);
        glVertex2f(70.0,40.0);
    glEnd();

    glColor3f(1.0f,0.0f,0.0f);

    glLoadIdentity();

    //Desenha triangulo
    glBegin(GL_TRIANGLES);
        glVertex2f(30,-20);
        glVertex2f(10, -60);
        glVertex2f(50, -60);
    glEnd();


    glFlush ();
}

void init (void)
{
/*  select clearing (background) color       */
    glClearColor (1.0, 1.0, 1.0, 1.0);

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Transformacoes 2D");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}

//#ingure -clude <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
#include <GL/freeglut.h>
#include "INF390.h"
#include <string>

struct retangulo {
  int estado = 0;
  double x = 0.0;
  double y = 0.0;
  string texto = "";
};

retangulo vet[13];

// void desenhaRetangulo() {
void desenhaRetangulo(int estado, double x, double y, const string &texto) {
  if(estado == 1)
    glColor3f(0, 1, 0);
  else if(estado == 3)
    glColor3f(0, 0, 1);

  glTranslatef(x, y, 0);
  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.0, 40.0);
  glVertex2f(100.0, 40.0);
  glVertex2f(100.0, 0.0);
  glEnd();
  glColor3f(1, 0, 0);
  INF390::texto(texto, x, y+10, 0.13, 0.13);
  glLoadIdentity();
}

void criaRetangulos() {
  for(int i = 0; i < 13; i++)
    vet[i].estado = 1;

  // vet[6].estado = 3;

  vet[0].x = -50;
  vet[0].y = 240;
  vet[0].texto = "INICIAR";

  vet[1].x = -160;
  vet[1].y = 160;
  vet[1].texto = "NORMAL";

  vet[2].x = -50;
  vet[2].y = 160;
  vet[2].texto = "RAPIDO";

  vet[3].x = 60;
  vet[3].y = 160;
  vet[3].texto = "TURBO";

  vet[4].x = -160;
  vet[4].y = 80;
  vet[4].texto = "20x10";

  vet[5].x = -50;
  vet[5].y = 80;
  vet[5].texto = "30x15";

  vet[6].x = 60;
  vet[6].y = 80;
  vet[6].texto = "50x25";

  vet[7].x = -160;
  vet[7].y = 0;
  vet[7].texto = "Cores1";

  vet[8].x = -50;
  vet[8].y = 0;
  vet[8].texto = "Cores2";

  vet[9].x = 60;
  vet[9].y = 0;
  vet[9].texto = "Cores3";

  vet[10].x = -105;
  vet[10].y = -80;
  vet[10].texto = "NORMAL";

  vet[11].x = 5;
  vet[11].y = -80;
  vet[11].texto = "BEBADO";

  vet[12].x = -50;
  vet[12].y = -160;
  vet[12].texto = "SAIR";
}

void INF390::texto(const std::string &texto, int x, int y, double tamanhoX, double tamanhoY)
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(x, y, 0);
  glScalef(tamanhoX, tamanhoY, 1.0);
  for (int i = 0; i < texto.length(); ++i)
  {
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, texto[i]);
  }
  glPopMatrix();
}

void handle_key(unsigned char key, int mousex, int mousey)
{
  switch(key)
  {
    case GLUT_KEY_UP:
      break;
    case GLUT_KEY_DOWN:
      break;
    case GLUT_KEY_LEFT:
      break;
    case GLUT_KEY_RIGHT:
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
  glVertex2f(300, 0);
  glVertex2f(-300, 0);
  glVertex2f(0, -300);
  glVertex2f(0, 300);
  glEnd();

  glPolygonMode(GL_FRONT, GL_FILL);

  for(int i = 0; i < 13; i++)
  {
    desenhaRetangulo(vet[i].estado, vet[i].x, vet[i].y, vet[i].texto);
  }

  glColor3f(1.0f, 0.0f, 0.0f);
  INF390::texto("VELOCIDADE:", -50, 210, 0.13, 0.13);
  INF390::texto("TAMANHO:", -50, 130, 0.13, 0.13);
  INF390::texto("CORES:", -50, 50, 0.13, 0.13);
  INF390::texto("MODO:", -50, -30, 0.13, 0.13);

  glFlush();
}

void init(void)
{
  /*  select clearing (background) color       */
  glClearColor(1.0, 1.0, 1.0, 1.0);

  /*  initialize viewing values  */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-300.0, 300.0, -300.0, 300.0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(200, 100);
  glutCreateWindow("Transformacoes 2D");
  criaRetangulos();
  init();
  glutKeyboardFunc(handle_key);
  glutDisplayFunc(display);

  glutMainLoop();
  return 0; /* ISO C requires main to return int. */
}

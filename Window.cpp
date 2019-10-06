#include <iostream>
#include <string>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "INF390.h"
#include "Tetris.h"
#include <chrono>
#include <thread>
#include <unistd.h>
using namespace std;

struct retangulo
{
  int estado = 0;
  double x = 0.0;
  double y = 0.0;
  string texto = "";
};

	int ultimaTecla = -1;


  retangulo vet[13];
  int atual = 0;
  int janelaAtiva = 0;    // 0 - menu, 1- jogo, 2- tela final
  int estadoJogo[4] = {}; // descreve o estado das configuracoes do jogo selecionadas no menu
	const int possiveisRotacoes[] = {0, 90, 180, 270};
 int larguraJogo;
	int alturaMaximaJogo;
	Tetris jogoComPecaCaindo(0);
  Tetris jogo(0);

	int alturaPecaAtual;
	char idPecaAtual = "IJLOSTZ"[rand() % 7];
	int posicaoPecaAtual;
  int rotacaoPecaAtual =0;
    bool primeiro = false;
int altura;
  int largura;

   int posinicialx = -150;
  int posinicialy = -300;




void iniciaRetangulos()
{
  for (int i = 0; i < 13; i++)
    vet[i].estado = 1;

  vet[0].estado = 2;
  vet[1].estado = 3;
  vet[4].estado = 3;
  vet[7].estado = 3;
  vet[10].estado = 3;

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

void desenhaContorno(double x, double y)
{
  glPushMatrix();
  glLineWidth(3);
  glTranslatef(x, y, 0);
  glColor3f(1, 0, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.0, 40.0);
  glVertex2f(100.0, 40.0);
  glVertex2f(100.0, 0.0);
  glEnd();
  glLineWidth(1);
  glPopMatrix();
}

void desenhaRetangulo(int estado, double x, double y, const string &texto)
{
  glPushMatrix();
  if (estado == 1 || estado == 2)
    glColor3f(0, 1, 0);
  else if (estado == 3 || estado == 4)
    glColor3f(0, 0, 1);

  glTranslatef(x, y, 0);
  glBegin(GL_POLYGON);
  glVertex2f(0.0, 0.0);
  glVertex2f(0.0, 40.0);
  glVertex2f(100.0, 40.0);
  glVertex2f(100.0, 0.0);
  glEnd();
  glColor3f(1, 0, 0);
  INF390::texto(texto, x, y + 10, 0.13, 0.13);
  glLoadIdentity();

  if (estado == 2 || estado == 4)
  {
    desenhaContorno(x, y);
  }
  glPopMatrix();
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

void handle_arrow_key_menu(int key, int x, int y)
{

  if  (janelaAtiva==0){
  switch (key)
  {
  case GLUT_KEY_UP:
    if (atual == 1 || atual == 2 || atual == 3)
    {
      vet[atual].estado--;
      vet[0].estado++;
      atual = 0;
    }
    if (atual == 4 || atual == 5 || atual == 6 || atual == 7 || atual == 8 || atual == 9)
    {
      vet[atual].estado--;
      vet[atual - 3].estado++;
      atual -= 3;
    }
    else if (atual == 10 || atual == 11)
    {
      vet[atual].estado--;
      vet[atual - 2].estado++;
      atual -= 2;
    }
    else if (atual == 12)
    {
      vet[atual].estado--;
      vet[atual - 1].estado++;
      atual--;
    }
    break;

  case GLUT_KEY_DOWN:
    if (atual == 0)
    {
      vet[atual].estado--;
      vet[atual + 1].estado++;
      atual = 1;
    }
    else if (atual == 1 || atual == 2 || atual == 3 || atual == 4 || atual == 5 || atual == 6 || atual == 7 || atual == 8)
    {
      vet[atual].estado--;
      vet[atual + 3].estado++;
      atual += 3;
    }
    else if (atual == 9 || atual == 10)
    {
      vet[atual].estado--;
      vet[atual + 2].estado++;
      atual += 2;
    }
    else if (atual == 11)
    {
      vet[11].estado--;
      vet[12].estado++;
      atual = 12;
    }
    break;

  case GLUT_KEY_LEFT:
    if (atual == 2 || atual == 3 || atual == 5 || atual == 6 || atual == 8 || atual == 9 || atual == 11)
    {
      vet[atual].estado--;
      vet[atual - 1].estado++;
      atual--;
    }
    break;

  case GLUT_KEY_RIGHT:
    if (atual == 1 || atual == 2 || atual == 4 || atual == 5 || atual == 7 || atual == 8 || atual == 10)
    {
      vet[atual].estado--;
      vet[atual + 1].estado++;
      atual++;
    }
    break;
  }
  }


    else if (janelaAtiva == 1)
  {


    switch (key)
    {
      case GLUT_KEY_LEFT:
      {
      
        ultimaTecla=0;
        break;
      }


        case GLUT_KEY_RIGHT:
        {
                  ultimaTecla=1;
          break;
        }


        case GLUT_KEY_UP:
        {
                ultimaTecla=2;
        break;
        }

        case GLUT_KEY_DOWN:
        {
          ultimaTecla = 3;
        }

      
    }
  }
  glutSwapBuffers();
  //glutPostRedisplay();
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-300.0, 300.0, -300.0, 300.0);
}

void desenhaQuadrado(int x, int y, double tam, bool preenchido)
{
  glTranslatef(x, y, 0);
  glColor3f(1, 0, 0);
  if (!preenchido)
  {
    glBegin(GL_LINE_LOOP);
    glVertex2d(0, 0);
    glVertex2d(0, tam);
    glVertex2d(tam, tam);
    glVertex2d(tam, 0);
    glEnd();
  }
  else
  {
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(0, tam);
    glVertex2d(tam, tam);
    glVertex2d(tam, 0);
    glEnd();
  }
  glLoadIdentity();


}

// void desenhaJogo(int altura, int largura) {

// }

void atualizaJogo()
{

  jogoComPecaCaindo = jogo;


	  if(ultimaTecla == 0)
		{ 
        			Tetris jogoTeste = jogoComPecaCaindo;

			if (jogoTeste.adicionaForma(posicaoPecaAtual - 1, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
				posicaoPecaAtual--;
        ultimaTecla = -1;

		}

  
		else if (ultimaTecla == 1)
		{
        			Tetris jogoTeste = jogoComPecaCaindo;

			if (jogoTeste.adicionaForma(posicaoPecaAtual + 1, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
				posicaoPecaAtual++;
                ultimaTecla = -1;

		}


		else if (ultimaTecla == 2)
		{ //a tecla de espaco e' utilizada para rodar a peca...
      			Tetris jogoTeste = jogoComPecaCaindo;

			if (jogoTeste.adicionaForma(posicaoPecaAtual, alturaPecaAtual, idPecaAtual, possiveisRotacoes[(rotacaoPecaAtual + 1) % 4]))
				rotacaoPecaAtual = (rotacaoPecaAtual + 1) % 4;
                ultimaTecla = -1;

		}

   
		//Antes de diminuirmos a altura de uma peca, tentamos adiciona-la nessa nova altura
		// Se a funcao retornar true --> significa que podemos diminuir
		// Senao --> isso significa que apeca colidiria (ocuparia o mesmo espaco que) com alguma peca fixa --> a peca devera parar na altura anterior
		// e uma nova peca deve comecar a cair

		if (jogoComPecaCaindo.adicionaForma(posicaoPecaAtual, alturaPecaAtual - 1, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
		{
			alturaPecaAtual--;
		}
		else
		{
			//adiciona a peca a posicao onde ela ficara fixada
			jogo.adicionaForma(posicaoPecaAtual, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]);
			jogoComPecaCaindo = jogo;

			//sorteia uma nova peca, define a altura como sendo o topo da tela, etc...
			idPecaAtual = "IJLOSTZ"[rand() % 7];
			posicaoPecaAtual = larguraJogo / 2 - 2;
			alturaPecaAtual = alturaMaximaJogo;
			rotacaoPecaAtual = rand() % 4;
			jogoComPecaCaindo.removeLinhasCompletas();
			jogo = jogoComPecaCaindo;
    }
		



}

void displayJogo(int value)
{
  janelaAtiva = 1;
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  






  if (estadoJogo[1] == 0)
  {
    altura = 20;
    largura = 10;
  }
  else if (estadoJogo[1] == 1)
  {
    altura = 30;
    largura = 15;
  }
  else if (estadoJogo[1] == 2)
  {
    altura = 50;
    largura = 25;
  }

  if (primeiro == false){
    Tetris jogo2(largura);
    jogo = jogo2;
      larguraJogo = largura;
  alturaPecaAtual=alturaMaximaJogo;
    posicaoPecaAtual = larguraJogo / 2 - 2;

    primeiro = true;

  }
  alturaMaximaJogo=altura;


 
  double tam = 300 / largura;

  atualizaJogo();

  //glClear(GL_COLOR_BUFFER_BIT);






    for (int i = 0; i < largura; i++) // i = x = largura
    {
      for (int j = 0; j < altura; j++) // j = y = altura
      {
        if (jogoComPecaCaindo.get(i, j) != ' ')
        {
          desenhaQuadrado(posicaoPecaAtual* tam + posinicialx,alturaPecaAtual * tam +posinicialy, tam, false);
        }
        else
        {
          desenhaQuadrado(i * tam +posinicialx , j * tam+posinicialy , tam, true);
        }
      }
      

    }
  glutSwapBuffers();
    glutTimerFunc(1000, displayJogo, 1);


}


void handle_key_menu(unsigned char key, int mousex, int mousey)
{
  if (janelaAtiva == 0)
  {
    switch (key)
    {
    case (unsigned char)13: // tecla ENTER
      if (atual == 0)
      {
        displayJogo(1);
      }
      if (atual == 1)
      {
        vet[atual].estado = 4;
        vet[2].estado = 1;
        vet[3].estado = 1;
        estadoJogo[0] = 0;
      }
      else if (atual == 2)
      {
        vet[atual].estado = 4;
        vet[1].estado = 1;
        vet[3].estado = 1;
        estadoJogo[0] = 1;
      }
      else if (atual == 3)
      {
        vet[atual].estado = 4;
        vet[1].estado = 1;
        vet[2].estado = 1;
        estadoJogo[0] = 2;
      }

      else if (atual == 4)
      {
        vet[atual].estado = 4;
        vet[5].estado = 1;
        vet[6].estado = 1;
        estadoJogo[1] = 0;
      }
      else if (atual == 5)
      {
        vet[atual].estado = 4;
        vet[4].estado = 1;
        vet[6].estado = 1;
        estadoJogo[1] = 1;
      }
      else if (atual == 6)
      {
        vet[atual].estado = 4;
        vet[4].estado = 1;
        vet[5].estado = 1;
        estadoJogo[1] = 2;
      }

      else if (atual == 7)
      {
        vet[atual].estado = 4;
        vet[8].estado = 1;
        vet[9].estado = 1;
        estadoJogo[2] = 0;
      }
      else if (atual == 8)
      {
        vet[atual].estado = 4;
        vet[7].estado = 1;
        vet[9].estado = 1;
        estadoJogo[2] = 1;
      }
      else if (atual == 9)
      {
        vet[atual].estado = 4;
        vet[7].estado = 1;
        vet[8].estado = 1;
        estadoJogo[2] = 2;
      }

      else if (atual == 10)
      {
        vet[atual].estado = 4;
        vet[11].estado = 1;
        estadoJogo[3] = 0;
      }
      else if (atual == 11)
      {
        vet[atual].estado = 4;
        vet[10].estado = 1;
        estadoJogo[3] = 1;
      }

      else if (atual == 12)
      {
        exit(0); // FECHAR
      }
    }
  
    }
  

  
        
      
  
    
  

  glutPostRedisplay();
}

void displayMenu()
{
  janelaAtiva = 0;
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Desenha Eixos
  // glLineWidth(1);
  // glBegin(GL_LINES);
  // glColor3f(0, 0, 0);
  // glVertex2f(300, 0);
  // glVertex2f(-300, 0);
  // glVertex2f(0, -300);
  // glVertex2f(0, 300);
  // glEnd();

  glPolygonMode(GL_FRONT, GL_FILL);

  for (int i = 0; i < 13; i++)
  {
    desenhaRetangulo(vet[i].estado, vet[i].x, vet[i].y, vet[i].texto);
  }

  glColor3f(1.0f, 0.0f, 0.0f);
  INF390::texto("VELOCIDADE:", -50, 210, 0.13, 0.13);
  INF390::texto("TAMANHO:", -50, 130, 0.13, 0.13);
  INF390::texto("CORES:", -50, 50, 0.13, 0.13);
  INF390::texto("MODO:", -50, -30, 0.13, 0.13);

  glFlush();
  return;
}

void display(void)
{
  if (janelaAtiva == 0)
  {
    glutSwapBuffers();
    displayMenu();
  }
  if (janelaAtiva == 1)
  {
    glutSwapBuffers();
    displayJogo(1);
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(200, 100);
  glutCreateWindow("Menu do Tetris");
  iniciaRetangulos();
  init();
  glutKeyboardFunc(handle_key_menu);
  glutSpecialFunc(handle_arrow_key_menu);
  
  glutDisplayFunc(display);



  glutMainLoop();
  return 0;
}

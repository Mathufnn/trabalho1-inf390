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

struct retangulo // Struct para representar os retangulos do menu principal
{
  int estado = 0; // Os estados sao: 0 - nao selecionado, 1 - selecionado, 2 - marcado previamente, 3 - selecionado e marcado previamente
  double x = 0.0; // Selecionar significa que o teclado esta sob essa opcao
  double y = 0.0;
  string texto = "";
};

int ultimaTecla = -1; // Variavel para armazenar ultima tecla pressionada valida

int executa;                                       // Variavel para inicializar valores inicias de um jogo (altura, largura, etc)
retangulo vet[13];                                 // Vetor que armazenara os dados de cada retangulo de opcoes
int atual = 0;                                     // Variavel para armazenar a opcao selecionada do menu
int janelaAtiva = 0;                               // Variavel que representa a janela que  esta ativa na tela0 - menu, 1- jogo, 2- tela final
int estadoJogo[4] = {};                            // Descreve o estado das configuracoes do jogo selecionadas no menu
const int possiveisRotacoes[] = {0, 90, 180, 270}; // Valores possiveis de rotacao do jogo
int larguraJogo;                                   // Variavel de largura do jogo
int alturaMaximaJogo;                              // Variavel de altura maxima que o jogo podera ter
int velocidade = 600;                              // Variavel   que define a velocidade da queda das pecas do jogo
bool perdeu = false;                               // Variavel que define se um jogo foi perdido ou nao
Tetris jogoComPecaCaindo(0);                       // Inicializacao para o jogo
Tetris jogo(0);                                    // Inicializacao para o jogo

int alturaPecaAtual;                      // Variavel usada no jogo
char idPecaAtual = "IJLOSTZ"[rand() % 7]; //  Pecas disponiveis no joog
int posicaoPecaAtual;                     // Variavel de inicializacao do jogo
int rotacaoPecaAtual = 0;                 // Variavel de inicializacao do jogo
bool primeiro = false;                    // Variavel que define se o jogo esta sendo executado pela primeira vez
int altura;                               // Variavel de altura do jogo
int largura;                              // Variavel de largura do jogo

int posinicialx = -150; // Posicao inicial de x na tela
int posinicialy = -300; // Posicao inicial de y na tela

void iniciaRetangulos() // Funcao para atribuicao de valores a cada retangulo do menu principal
{                       // Cada retangulo possui um estado e eh atraves dele que decidimos qual configuracao o jogo tera
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

void desenhaContorno(double x, double y) // Funcao para desenho de contornos nos retangulos do menu principal
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

void desenhaRetangulo(int estado, double x, double y, const string &texto) // Funcao de desenho de retangulos no menu principal
{
  glPushMatrix();
  if (estado == 1 || estado == 2)
  {
    glColor3f(0, 1, 0);
  }
  else if (estado == 3 || estado == 4)
  {
    glColor3f(0, 0, 1);
  }

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

void INF390::texto(const std::string &texto, int x, int y, double tamanhoX, double tamanhoY) // Funcao de escrita de texto na tela
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

void handle_arrow_key_menu(int key, int x, int y) // Tratamento de setas em cada janel
{
  if (janelaAtiva == 0)
  {
    switch (key)
    {
    case GLUT_KEY_UP: // Na janela 0 a navegacao eh de cima para baixo e dos lados, obedecendo a ordem da direita para a esquerda
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
    glutPostRedisplay();
  }

  else if (janelaAtiva == 1) // No caso da janela 1 (jogo executando), eh setado valores para ultimaTecla que serao tratados na funcao de displayJogo
  {                          // Cada key recebida pelo teclado executara seu respectivo movimento na tela do jogo atraves da variavel ultimaTecla

    switch (key)
    {
    case GLUT_KEY_LEFT:
    {

      ultimaTecla = 0;

      break;
    }

    case GLUT_KEY_RIGHT:
    {
      ultimaTecla = 1;
      break;
    }

    case GLUT_KEY_DOWN:
    {
      ultimaTecla = 3;
      break;
    }
    }
  }
}

void init(void) // Funcao de inicializacao da tela
{
  glClearColor(1.0, 1.0, 1.0, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-300.0, 300.0, -300.0, 300.0);
}

void desenhaQuadrado(int x, int y, double tam, bool preenchido) // Funcao responsavel por desenhar quadrados do jogo
{                                                               // Eh chamada toda vez que a displayJogo eh executada, de forma a atualizar a tela com a posicao atual das pecas do jogo
  glTranslatef(x, y, 0);

  if (!preenchido) // Tratamento para o caso de ser um quadrado que parte de uma peca, se a variavel preenchido for verdadeira,
  {                // O quadrado nao eh preenchido
    if (estadoJogo[2] == 0)
      glColor3f(0.9, 0.9, 0.9);
    else if (estadoJogo[2] == 1)
      glColor3f(0, 1, 1);
    else if (estadoJogo[2] == 2)
      glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(0, tam);
    glVertex2d(tam, tam);
    glVertex2d(tam, 0);
    glEnd();
  }
  else // Desenho dos locais que contem pecas (quadrados preenchidos)
  {
    if (estadoJogo[2] == 0)
      glColor3f(0, 0, 0);
    else if (estadoJogo[2] == 1)
      glColor3f(1, 0, 0);
    else if (estadoJogo[2] == 2)
      glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(0, tam);
    glVertex2d(tam, tam);
    glVertex2d(tam, 0);
    glEnd();
  }
  glLoadIdentity();
}

void displayPerdeu(int value) // Funcao de display que desenha na tela caso o usuario perca o jogo
{                             // Eh chamada quando nao ha como adicionar novas pecas na tela e pode retornar ao menu principal atraves da tecla ESC
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glColor3f(1.0f, 0.0f, 0.0f);

  INF390::texto("VOCE PERDEU!", -50, 150, 0.13, 0.19);
  glutSwapBuffers();
}

void atualizaJogo() // Funcao que processa o posicionamento das pecas e trata a logica do jogo, como movimentos, reducao de colunas preenchidas, fronteiras, etc
{                   // Logica adaptada da funcao jogoTetris.cpp vinculada ao trabalho original
  jogoComPecaCaindo = jogo;

  if (ultimaTecla == 0)
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
  {
    Tetris jogoTeste = jogoComPecaCaindo;

    if (jogoTeste.adicionaForma(posicaoPecaAtual, alturaPecaAtual, idPecaAtual, possiveisRotacoes[(rotacaoPecaAtual + 1) % 4]))
      rotacaoPecaAtual = (rotacaoPecaAtual + 1) % 4;
    ultimaTecla = -1;
  }

  else if (ultimaTecla == 3)
  {
    Tetris jogoTeste = jogoComPecaCaindo;

    if (jogoTeste.adicionaForma(posicaoPecaAtual, alturaPecaAtual - 1, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
    {
      alturaPecaAtual--;
    }
    ultimaTecla = -1;
  }

  if (jogoComPecaCaindo.adicionaForma(posicaoPecaAtual, alturaPecaAtual - 1, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
  {
    alturaPecaAtual--;
  }
  else
  {
    if (jogo.adicionaForma(posicaoPecaAtual, alturaPecaAtual, idPecaAtual, possiveisRotacoes[rotacaoPecaAtual]))
    {

      jogoComPecaCaindo = jogo;

      idPecaAtual = "IJLOSTZ"[rand() % 7];
      posicaoPecaAtual = larguraJogo / 2 - 2;
      alturaPecaAtual = alturaMaximaJogo;
      rotacaoPecaAtual = rand() % 4;
      jogoComPecaCaindo.removeLinhasCompletas();
      jogo = jogoComPecaCaindo;
    }
    else // Caso nao seja possivel adicionar a peca, a variavel perdeu fica true e a tela de derrota eh renderizada em seguida
    {
      perdeu = true;
    }
  }
}

int contadorIteracoes = 0;
void rotacionaTela(int value)
{
  glRotatef(30, 0, 0, 1);
  cout << contadorIteracoes++ << endl;
  glutTimerFunc(3000, rotacionaTela, 1);
  glutPostRedisplay();
}

void displayJogo(int value) // Funcao chamada de tempos em tempos para renderizacao da tela do jogo (janela 2)
{
  if (!perdeu) // Caso o jogador nao tenha perdido, a tela sera renderizada
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (executa != 0) // A variavel executa quando diferente de 0 (caso em que ESC e pressionado), permite que o jogo siga seu caminho logico de execucao
    {

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

      alturaMaximaJogo = altura;

      double tam = 300 / largura;

      if (primeiro == false)
      {
        idPecaAtual = "IJLOSTZ"[rand() % 7];
        Tetris jogo2(largura);
        jogo = jogo2;
        larguraJogo = largura;
        alturaPecaAtual = alturaMaximaJogo;
        posicaoPecaAtual = larguraJogo / 2 - 2;

        primeiro = true;
      }

      atualizaJogo();

      for (int i = 0; i < largura; i++) // Logica do desenho na tela: caso a posicao na matriz do jogo seja uma letra, entao o quadrado sera preenchido, caso contrario nao sera
      {
        for (int j = 0; j < altura; j++)
        {
          if (jogoComPecaCaindo.get(i, j) != ' ')
          {
            desenhaQuadrado(i * tam + posinicialx, j * tam + posinicialy, tam, true);
          }
          else
          {
            desenhaQuadrado(i * tam + posinicialx, j * tam + posinicialy, tam, false);
          }
        }
      }

      glutTimerFunc(velocidade, displayJogo, 1); // A velocidade do jogo e definida pelas opcoes marcadas no menu principal, atraves da variavel velocidade
      glutSwapBuffers();
    }
  }
  if (perdeu == true) // Se o usuario perder o jogo, entao uma nova tela sera renderizada
  {
    janelaAtiva = 2;
    glutTimerFunc(500, displayPerdeu, 1);
  }
}

void displayMenu(int value) // Funcao para desenho do menu principal do jogo
{
  if (janelaAtiva == 0)
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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
  }
}

void trataSelecaoDeBotao(int atual)
{
  for (int i = 0; i < 13; i++)
  {
    if (vet[i].estado == 2 || vet[i].estado == 4)
      vet[i].estado--;
  }
  if (atual == 0)
  {
    executa = 1;
    janelaAtiva = 1;
    perdeu = false;
  }
  if (atual == 1) // Atual 1, 2, 3 sao referentes a configuracoes de velocidade do jogo
  {
    vet[atual].estado = 4;
    vet[2].estado = 1;
    vet[3].estado = 1;
    estadoJogo[0] = 0;
    velocidade = 600;
  }
  else if (atual == 2)
  {
    vet[atual].estado = 4;
    vet[1].estado = 1;
    vet[3].estado = 1;
    estadoJogo[0] = 1;
    velocidade = 200;
  }
  else if (atual == 3)
  {
    vet[atual].estado = 4;
    vet[1].estado = 1;
    vet[2].estado = 1;
    estadoJogo[0] = 2;
    velocidade = 70;
  }

  else if (atual == 4) // atual com valor 4,5,6 sao referentes a tamanhos de jogo pre-definidos (20x10, 30x15, 50x25)
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

  else if (atual == 7) // atual com valor 7,8 e 9 sao referentes as cores do jogo
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

  else if (atual == 10) // atual com valor 10,11 sao referentes aos modos de jogo
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

  else if (atual == 12) // atual com valor 12 indica fechamento do jogo
  {
    exit(0); // FECHAR
  }
}

void handle_key_menu(unsigned char key, int mousex, int mousey) // Tratamento de entrada de teclas enter, esc e espaco do teclado
{

  if (janelaAtiva == 0)
  {
    switch (key)
    {
    case (unsigned char)13: // Na tela 1, o enter inicia o jogo caso a opcao atual seja 0
      trataSelecaoDeBotao(atual);
    }

    glutPostRedisplay();
  }

  if (janelaAtiva == 1) // caso a janela ativa seja a 1 (referente ao jogo executando), as teclas tratadas serao espaco e esc
  {
    switch (key)
    {
    case ' ': // espaco seta a variavel ultimaTecla para 2, o que gera uma rotacao em atualizaJogo

      ultimaTecla = 2;

      break;

    case (unsigned char)27: // esc seta a variavel executa para 0, interrompendo a renderizacao da tela e retornando a tela inicial (janelaAtiva=0)

      executa = 0;
      primeiro = false;
      ultimaTecla = -1;
      janelaAtiva = 0;
      atual = 0;
      glutPostRedisplay();
      break;
    }
  }

  if (janelaAtiva == 2)       // no caso da janela 2 (janela de jogo perdido) o jogo eh interrompido (executa =0), os valores do jogo sao reiniciados (primeiro = false)
  {                           // e a janela retorna ao menu principal (janelaAtiva=0)

    switch (key)
    {
    case (unsigned char)27:
      executa = 0;
      primeiro = false;
      ultimaTecla = -1;

      janelaAtiva = 0;
      glutPostRedisplay();
      break;
    }
  }
}

void HandleMouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    for (int i = 0; i < 13; i++)
    {
      if (x <= vet[i].x + 400 && x >= vet[i].x + 300 && y <= -vet[i].y + 300 && y >= -vet[i].y + 260)
      {
        trataSelecaoDeBotao(i);
      }
    }
  }
}

void reshape(int w, int h)      // Funcao para redimensionamento da tela
{
  glViewport((w - 600) / 2 - ((h - 600) / 2), 0, (GLsizei)h, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-300, 300, -300, 300);
}

void display(void)      // Funcao para telas de display
{
  if (janelaAtiva == 0)
  {

    displayMenu(1);
  }
  else if (janelaAtiva == 1 && estadoJogo[3] == 1)
  {
    rotacionaTela(1);
    displayJogo(1);
  }
  else if (janelaAtiva == 1)
  {
    displayJogo(1);
  }

  else if (janelaAtiva == 2)
  {
    displayPerdeu(1);
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(200, 100);
  glutCreateWindow("Tetris");
  iniciaRetangulos();
  init();
  glutKeyboardFunc(handle_key_menu);
  glutSpecialFunc(handle_arrow_key_menu);
  glutMouseFunc(HandleMouse);
  //special serve pras setas, a keyboard pro ESC, Enter e espaço
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMainLoop();
  return 0;
}

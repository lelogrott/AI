//compile: g++ -std=c++11 main_dijkstra.cpp -o robotdijkstra lista.c -lsfml-graphics -lsfml-window -lsfml-system -O3

#include "util.h"
#include "robot.h"
#include "Lista.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <unistd.h>
// #include <Color.hpp>
void mostra_inteiro(void *info);
void dijkstra(int **matAdj, int vertInicial);
int extrairMin(int **matAdj, int *dist, int *visitados);

void draw_board(sf::RenderWindow & windowRef, int **board, int board_size, int *visited)
{
  sf::Color white(255, 255, 255);
  sf::Color black(0, 0, 0);
  sf::Color red(255, 0, 0);
  sf::Color dark_red(128, 0, 0);
  sf::Color green(0, 255, 0);
  sf::Color dark_green(0, 102, 34);
  sf::Color blue(0, 0, 255);
  sf::Color dark_blue(0, 32, 128);
  sf::Color yellow(255, 228, 15);
  sf::Color green_1(140, 195, 110);
  sf::Color brown(144, 135, 96);
  sf::Color dark_brown(115, 77, 38);
  sf::Color bright_red(231, 108, 86);
  sf::Color bright_orange(241, 176, 102);
  sf::Color bright_green_yellow(169, 199, 35);
  sf::Color bright_green(88, 171, 45);
  sf::Color bright_blue_green(43, 151, 89);
  sf::Color bright_blue(0, 147, 159);
  sf::Color bright_purple_blue(59, 130, 157);
  sf::Color bright_purple(178, 137, 166);
  sf::Color bright_purple_red(209, 100, 109);

  windowRef.clear(white);
  for (int i = 0; i < board_size; ++i)
  {
    for (int j = 0; j < board_size; ++j)
    {
      sf::RectangleShape rectangle;
      rectangle.setSize(sf::Vector2f(1, 1));
      rectangle.setPosition(i, j);
      sf::CircleShape square(0.5, 4);
      square.setPosition(i, j);
      int position = j*BOARD_SIZE + i;
      if(board[j][i]==5)
      {
        rectangle.setFillColor(brown);
        if (visited[position]==1)
        {
          rectangle.setFillColor(dark_brown);
        }
        windowRef.draw(rectangle);
        if (visited[position]==2)
        {
          square.setFillColor(dark_brown);
          windowRef.draw(square);
        }
      }
      else if (board[j][i]==10)
      {
        rectangle.setFillColor(blue);
        if (visited[position]==1)
        {
          rectangle.setFillColor(dark_blue);
        }
        windowRef.draw(rectangle);
        if (visited[position]==2)
        {
          square.setFillColor(dark_blue);
          windowRef.draw(square);
        }
      }
      else if (board[j][i]==15)
      {
        rectangle.setFillColor(red);
        if (visited[position]==1)
        {
          rectangle.setFillColor(dark_red);
        }
        windowRef.draw(rectangle);
        if (visited[position]==2)
        {
          square.setFillColor(dark_red);
          windowRef.draw(square);
        }
      }
      else if (board[j][i]==1)
      {
        rectangle.setFillColor(green);
        if (visited[position]==1)
        {
          rectangle.setFillColor(dark_green);
        }
        windowRef.draw(rectangle);
        if (visited[position]==2)
        {
          square.setFillColor(dark_green);
          windowRef.draw(square);
        }
      }
      else if (board[i][j]==90)
      {
        rectangle.setFillColor(green_1);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==6)
      {
        rectangle.setFillColor(brown);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==7)
      {
        rectangle.setFillColor(bright_red);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==8)
      {
        rectangle.setFillColor(bright_orange);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==9)
      {
        rectangle.setFillColor(bright_green_yellow);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==100)
      {
        rectangle.setFillColor(bright_green);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==11)
      {
        rectangle.setFillColor(bright_blue_green);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==12)
      {
        rectangle.setFillColor(bright_blue);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==13)
      {
        rectangle.setFillColor(bright_purple_blue);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==14)
      {
        rectangle.setFillColor(bright_purple);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==150)
      {
        rectangle.setFillColor(bright_purple_red);
        windowRef.draw(rectangle);
      }
    }
  }
}

sf::RenderWindow window(sf::VideoMode(BOARD_SIZE, BOARD_SIZE), "ROBOT");
sf::RenderWindow windows(sf::VideoMode(BOARD_SIZE, BOARD_SIZE), "ROBOT");

int** cria_matriz(int **field)
{
  int i,j;
  int **matriz = NULL;
  matriz = (int**)malloc(sizeof(int*) * (BOARD_SIZE * BOARD_SIZE));

  for (i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
  {
    matriz[i] = (int*)malloc(sizeof(int)*(BOARD_SIZE*BOARD_SIZE));
  }
  for (i = 0; i <  BOARD_SIZE * BOARD_SIZE; ++i)
  {
    for (j = 0; j < BOARD_SIZE * BOARD_SIZE; ++j)
    {
      matriz[i][j] = -1;
    }
  }

  for (i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
  {
    if (i % BOARD_SIZE != 0) // does have left neighbor
    {
      matriz[i][i-1] = field[i/BOARD_SIZE][i%BOARD_SIZE];
    }
    if (i - BOARD_SIZE >= 0 ) // does have up neighbor
    {
      matriz[i][i-42] = field[i/BOARD_SIZE][i%BOARD_SIZE];
    }
    if ((i + 1 ) % BOARD_SIZE != 0) // does have right neighbor
    {
      matriz[i][i+1] = field[i/BOARD_SIZE][i%BOARD_SIZE];
    }
    if (i + BOARD_SIZE < BOARD_SIZE*BOARD_SIZE) // does have down neighbor
    {
      matriz[i][i+42] = field[i/BOARD_SIZE][i%BOARD_SIZE];
    }
  }
  return matriz;
}


void dijkstra(int **field, int vertInicial)
{
  int *dist, *visitados;
  int i, j, u;
  int **matAdj = NULL;
  matAdj = cria_matriz(field);
  //Lista de Precendentes
  Lista precedentes;
  inicializa_lista(&precedentes, sizeof(Lista));

  // Alocacao para a matAdj[tamMax][tamMax]
  
  //Alocacao da matriz que guarda as distancias
  dist = (int*)malloc(sizeof(int) * BOARD_SIZE * BOARD_SIZE);
  for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    dist[i] = INF;

  visitados = (int*)calloc(BOARD_SIZE * BOARD_SIZE, sizeof(int));

  //Insere nListas para marcar os precedentes.
  for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
  {
    Lista l;
    inicializa_lista(&l, sizeof(int));
    insereNoFim(&precedentes, &l);
  }

    // Distancia do proprio vertice inicial e sempre 0
    dist[vertInicial] = 0;

    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    { 
    //Extrai o vertice com a menor distancia e que ainda nao foi visitado
      u = extrairMin(matAdj, dist, visitados);

    //Marca como visitado
      visitados[u] = 1;
      if (field[u/BOARD_SIZE][u%BOARD_SIZE] == 666)
      {
        printf("encontrou objetivo.\n");
        break;
      }

    //For de 0 at[e BOARD_SIZE (Numero maximo que dijkstra roda)
        for (j = 0; j < BOARD_SIZE * BOARD_SIZE; j++)
        {
          draw_board(window, field, BOARD_SIZE, visitados);
          window.display();
          sf::Event event;
          while (window.pollEvent(event))
          {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
              window.close();
              //print=0;
              break;
            }
          }
            if (!visitados[j] && matAdj[u][j] != -1 && dist[u] != INF && dist[u]+matAdj[u][j] <= dist[j])
            {
        //Se a distancia do no inicial, ate o no atual + ate o no de menor distancia 
        //For igual, adicione-o na lista tambem como um no precedente
                if (dist[u]+matAdj[u][j] == dist[j])
                {
                    Lista l;
                    removeNaPosicao(&precedentes, &l, j);
                    insereNoFim(&l, &u);
                    insereNaPosicao(&precedentes, &l, j);
                }
        //Se nao for, retire todos os nos precedentes, e coloque o novo no precedente.
                else
                {
                    Lista l;
                    removeNaPosicao(&precedentes, &l, j);
                    limpa_lista(&l);
                    insereNoFim(&l, &u);
                    insereNaPosicao(&precedentes, &l, j);
                }
        //Atualize a distancia
                dist[j] = dist[u] + matAdj[u][j];
            }
        }

    }
  //Imprime
    // printf("VERTICES   : ");
    // for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    //     printf("%d  ", i);
    // printf("\n");
    // printf("ESTIMATIVAS: ");
    // for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    //     printf("%d  ", dist[i]);
    // printf("\n");
    printf("\nDistancias:\n");
    //for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        printf("Vertice %d ao vertice %d: %d\n", vertInicial, u, dist[u]);
    }
    printf("PRECEDENTES:\n");
   //for (i = 0; i < u; i++)
      visitados[u] = 2;
    while(u != vertInicial)
    {
        printf("Precedente(s) vertice %d: ", u);
        Lista l;
        leNaPosicao(&precedentes, &l, u);
        mostra_lista(l, mostra_inteiro);
        leNaPosicao(&l, &u, 0);
      visitados[u] = 2;

        printf("\n");
    }


  printf("\n");
  int print = 1;

  while(print==1)
  {
    draw_board(windows, field, BOARD_SIZE, visitados);
    windows.display();
    sf::Event event;
    while (windows.pollEvent(event))
    {
      // "close requested" event: we close the windows
      if (event.type == sf::Event::Closed)
      {
        windows.close();
        print=0;
        break;
      }
    }
  }


}

// Funcao para extrair o no que tem menor distancia
int extrairMin(int **matAdj, int *dist, int *visitados)
{
    int min = INF;
    int min_index;
    int v;
    for(v = 0; v < BOARD_SIZE * BOARD_SIZE; v++)
    {
        if(!visitados[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void mostra_inteiro(void *info)
{
    int *n = (int*) info;
    printf("%d ", *n);
}


int main(int argc, char const *argv[])
{
  int **field = NULL;
  int i, j;
  
  if (allocate(&field, BOARD_SIZE, BOARD_SIZE) == DAMN_GIRL)
  {
    printf("\n>>SHIIIIIT! Error on allocate.\n");
    return DAMN_GIRL;
  }
  
  read_file_into_matrix(&field, BOARD_SIZE, BOARD_SIZE);

  
  field[41][41] = 666;

  
  dijkstra(field, INITIAL_POS);

  return 0;
}
  
 


    

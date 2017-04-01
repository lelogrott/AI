//compile: g++ -std=c++11 main.cpp -o ants Ant.c -lsfml-graphics -lsfml-window -lsfml-system -O3

#include "Util.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>


void draw_board(sf::RenderWindow & windowRef, int **board, int **live_ants_board, int BOARD_SIZE)
{
  windowRef.clear(sf::Color::White);
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      sf::RectangleShape rectangle;
      rectangle.setSize(sf::Vector2f(1, 1));
      rectangle.setPosition(i, j);
      if(board[i][j]==-1)
      {
        rectangle.setFillColor(sf::Color::Red);
        windowRef.draw(rectangle);
      }
      if (live_ants_board[i][j]==1)
      {
        rectangle.setFillColor(sf::Color::Black);
        windowRef.draw(rectangle);
      }
      
    }
  }
}

int main(int argc, char const *argv[]){

  struct timeval timevalA;
  struct timeval timevalB;

  int BOARD_SIZE = atoi(argv[1]);
  int N_LIVE_ANTS = atoi(argv[2]);
  int N_DEAD_ANTS = atoi(argv[3]);
  int FOV_RANGE  = atoi(argv[4]);

  srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode(160, 160), "Ants");

  pPair coords;
  Pair old_position, new_position;
  generate_coords(&coords);
  


  int i, it=0;
  int print = 1;
  while (print) {
    draw_board(window, board, live_ants_board, BOARD_SIZE);
    window.display();
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
      {
        window.close();
        print = 0;
        break;
      }
    }
  }
  gettimeofday(&timevalA,NULL);
  while(it < 3000000)
  {
    // if (it%1000==0)
    // {
    //   draw_board(window, board, live_ants_board);
    //   window.display();it=0;
    // }
    // sf::Event event;
    // while (window.pollEvent(event))
    // {
    //   // "close requested" event: we close the window
    //   if (event.type == sf::Event::Closed)
    //   {
    //     window.close();
    //     return 0;
    //   }
    // }
    for (i = 0; i < N_LIVE_ANTS; ++i)
    {
      if (live_ants[i].loaded == NAO)
      {
        if ((board[live_ants[i].position.i][live_ants[i].position.j] == -1) && (should_pick_up(board, live_ants[i], BOARD_SIZE)==SIM))
        {
          pick_up_ant(&board, &live_ants[i]);
        }
      }
      else if (live_ants[i].loaded == SIM)
      {
        if ((board[live_ants[i].position.i][live_ants[i].position.j] == 0) && (should_drop_off(board, live_ants[i], BOARD_SIZE)==SIM))
        {
          drop_off_ant(&board, &live_ants[i]);
        } 
      }
      move(board, live_ants_board, coords, &old_position, &new_position, &live_ants[i], BOARD_SIZE);
      live_ants_board[old_position.i][old_position.j] = 0;
      live_ants_board[new_position.i][new_position.j] = 1;
    }
    it++;
  }
  gettimeofday(&timevalB,NULL);
  printf("\ntempo de execucao: %lf\n", timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000);

  print =1;
  sf::RenderWindow windows(sf::VideoMode(160, 160), "Ants");
  while (print) {
    draw_board(windows, board, live_ants_board, BOARD_SIZE);
    windows.display();
    sf::Event event;
    while (windows.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
      {
        windows.close();
        print = 0;
        break;
      }
    }
    
  }
  // show_board(board, "DEAD ANTS BOARD");
  

  return 0;  
}


    

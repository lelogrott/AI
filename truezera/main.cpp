//compile: g++ -std=c++11 main.cpp -o ants Ant.c -lsfml-graphics -lsfml-window -lsfml-system -O3

#include "Util.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

void draw_board(sf::RenderWindow & windowRef, int **board, int **live_ants_board)
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

int main(){

  srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode(160, 160), "Ants");

  pPair coords;
  Pair old_position, new_position;
  generate_coords(&coords);
  

  pData data_array;
  int **plot_board, **live_ants_board;

  generate_live_ants_array(&live_ants, N_LIVE_ANTS, FOV_RANGE);

  generate_data_array(&data_array, 400);


  generate_data_board_for_plot(&plot_board, 400, data_array);

 
  generate_live_ants_board(&live_ants_board, N_LIVE_ANTS, live_ants);

  int i, it=0;

  while(true)
  {
    if (it%10000==0)
    {
      draw_board(window, board, live_ants_board);
      window.display();it=0;
    }
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
      {
        window.close();
        return 0;
      }
    }
    for (i = 0; i < N_LIVE_ANTS; ++i)
    {
      if (live_ants[i].loaded == NAO)
      {
        if ((board[live_ants[i].position.i][live_ants[i].position.j] == -1) && (should_pick_up(board, live_ants[i])==SIM))
        {
          pick_up_ant(&board, &live_ants[i]);
        }
      }
      else if (live_ants[i].loaded == SIM)
      {
        if ((board[live_ants[i].position.i][live_ants[i].position.j] == 0) && (should_drop_off(board, live_ants[i])==SIM))
        {
          drop_off_ant(&board, &live_ants[i]);
        } 
      }
      move(board, live_ants_board, coords, &old_position, &new_position, &live_ants[i]);
      live_ants_board[old_position.i][old_position.j] = 0;
      live_ants_board[new_position.i][new_position.j] = 1;
    }
    it++;
  }
  // show_board(board, "DEAD ANTS BOARD");
  

  return 0;  
}


    

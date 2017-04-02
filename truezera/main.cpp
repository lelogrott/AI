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
      if(board[i][j]==1)
      {
        rectangle.setFillColor(sf::Color::Red);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==2)
      {
        rectangle.setFillColor(sf::Color::Blue);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==3)
      {
        rectangle.setFillColor(sf::Color::Green);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==4)
      {
        rectangle.setFillColor(sf::Color::Yellow);
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
  
  pAnt live_ants;
  pData data_array;
  ppData data_board;
  int **plot_board, **live_ants_board;

  generate_live_ants_array(&live_ants, N_LIVE_ANTS, FOV_RANGE);

  generate_data_array(&data_array, 400);

  generate_data_board_for_plot(&plot_board, 400, data_array);
 
  generate_live_ants_board(&live_ants_board, N_LIVE_ANTS, live_ants);

  generate_and_populate_data_board_for_calc(&data_board, 400, data_array);

  //show_board(plot_board, "DATA");  
  
  while(true)
  {
    if (it%10000==0)
    {
      draw_board(window, plot_board, live_ants_board);
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
        if ((data_board[live_ants[i].position.i][live_ants[i].position.j] == -1) && (should_pick_up_data(data_board, live_ants[i])==SIM))
        {
          pick_up_ant(&data_board, &live_ants[i]);
        }
      }
      else if (live_ants[i].loaded == SIM)
      {
        if ((data_board[live_ants[i].position.i][live_ants[i].position.j] == 0) && (should_drop_off_data(data_board, live_ants[i])==SIM))
        {
          drop_off_ant(&data_board, &live_ants[i]);
        } 
      }
      move(data_board, live_ants_board, coords, &old_position, &new_position, &live_ants[i]);
      live_ants_board[old_position.i][old_position.j] = 0;
      live_ants_board[new_position.i][new_position.j] = 1;
    }
    it++;
  }
  
  // show_board(board, "DEAD ANTS BOARD");
  

  return 0;  
}


    

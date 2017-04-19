//compile: g++ -std=c++11 main.cpp -o ants Ant.c -lsfml-graphics -lsfml-window -lsfml-system -O3

#include "Util.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
// #include <Color.hpp>

void draw_board(sf::RenderWindow & windowRef, ppData board, int **live_ants_board, int BOARD_SIZE)
{
  sf::Color white(255, 255, 255);
  sf::Color black(0, 0, 0);
  sf::Color red(255, 0, 0);
  sf::Color green(0, 255, 0);
  sf::Color blue(0, 0, 255);
  sf::Color yellow(255, 228, 15);
  sf::Color green_1(140, 195, 110);
  sf::Color brown(144, 135, 96);
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
  for (int i = 0; i < BOARD_SIZE; ++i)
  {
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
      sf::RectangleShape rectangle;
      rectangle.setSize(sf::Vector2f(1, 1));
      rectangle.setPosition(i, j);
      
      if(board[i][j].type==1)
      {
        rectangle.setFillColor(red);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==2)
      {
        rectangle.setFillColor(blue);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==3)
      {
        rectangle.setFillColor(green);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==4)
      {
        rectangle.setFillColor(yellow);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==5)
      {
        rectangle.setFillColor(green_1);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==6)
      {
        rectangle.setFillColor(brown);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==7)
      {
        rectangle.setFillColor(bright_red);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==8)
      {
        rectangle.setFillColor(bright_orange);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==9)
      {
        rectangle.setFillColor(bright_green_yellow);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==10)
      {
        rectangle.setFillColor(bright_green);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==11)
      {
        rectangle.setFillColor(bright_blue_green);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==12)
      {
        rectangle.setFillColor(bright_blue);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==13)
      {
        rectangle.setFillColor(bright_purple_blue);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==14)
      {
        rectangle.setFillColor(bright_purple);
        windowRef.draw(rectangle);
      }
      else if (board[i][j].type==15)
      {
        rectangle.setFillColor(bright_purple_red);
        windowRef.draw(rectangle);
      }
      if (live_ants_board[i][j]==1)
      {
        rectangle.setFillColor(black);
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
  sf::RenderWindow window(sf::VideoMode(BOARD_SIZE, BOARD_SIZE), "Ants");

  pPair coords;
  Pair old_position, new_position;
  generate_coords(&coords);
  
  pAnt live_ants;
  pData data_array;
  ppData data_board;
  int **live_ants_board;

  double max_dist;

  generate_live_ants_array(&live_ants, N_LIVE_ANTS, FOV_RANGE, BOARD_SIZE);

  generate_data_array(&data_array, 600, &max_dist, BOARD_SIZE);

  generate_live_ants_board(&live_ants_board, N_LIVE_ANTS, live_ants, BOARD_SIZE);

  generate_and_populate_data_board_for_calc(&data_board, 600, data_array, BOARD_SIZE);

  int print = 1;
  while(print)
  {
    draw_board(window, data_board, live_ants_board, BOARD_SIZE);
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
  //show_board(plot_board, "DATA");  
  gettimeofday(&timevalA, NULL);
  int i, it=0;
  while(it < 3000000)
  {
    // if (it%10000==0)
    // {
    //   draw_board(window, data_board, live_ants_board, BOARD_SIZE);
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
        if ((data_board[live_ants[i].position.i][live_ants[i].position.j].type != -1) && (should_pick_up_data(data_board, live_ants[i], max_dist, BOARD_SIZE)==SIM))
        {
          pick_up_data(&data_board, &live_ants[i]);
          // printf("pegou\n");
        }
      }
      else if (live_ants[i].loaded == SIM)
      {
        if ((data_board[live_ants[i].position.i][live_ants[i].position.j].type == -1) && (should_drop_off_data(data_board, live_ants[i], max_dist, BOARD_SIZE)==SIM))
        {
          drop_off_data(&data_board, &live_ants[i]);
          // printf("soltou\n");
        } 
      }
      move(live_ants_board, coords, &old_position, &new_position, &live_ants[i], BOARD_SIZE);
      live_ants_board[old_position.i][old_position.j] = 0;
      live_ants_board[new_position.i][new_position.j] = 1;
    }
    it++;
  }
  
  // show_board(board, "DEAD ANTS BOARD");
    
  gettimeofday(&timevalB, NULL);
  printf("\ntempo de execucao: %lf\n", timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000);

  print =1;
  sf::RenderWindow windows(sf::VideoMode(BOARD_SIZE, BOARD_SIZE), "Ants");
  while (print) {
    draw_board(windows, data_board, live_ants_board, BOARD_SIZE);
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


    

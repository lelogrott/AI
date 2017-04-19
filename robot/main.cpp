//compile: g++ -std=c++11 main.cpp -o ants Ant.c -lsfml-graphics -lsfml-window -lsfml-system -O3

#include "util.h"
#include "robot.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
// #include <Color.hpp>

void draw_board(sf::RenderWindow & windowRef, int **board, int BOARD_SIZE)
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
      
      if(board[i][j]==1)
      {
        rectangle.setFillColor(brown);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==2)
      {
        rectangle.setFillColor(blue);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==3)
      {
        rectangle.setFillColor(red);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==0)
      {
        rectangle.setFillColor(green);
        windowRef.draw(rectangle);
      }
      else if (board[i][j]==5)
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
      else if (board[i][j]==10)
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
      else if (board[i][j]==15)
      {
        rectangle.setFillColor(bright_purple_red);
        windowRef.draw(rectangle);
      }
    }
  }
}



int main(int argc, char const *argv[])
{
  int **field = NULL;
  
  if (allocate(&field, BOARD_SIZE, BOARD_SIZE) == DAMN_GIRL)
  {
    printf("\n>>SHIIIIIT! Error on allocate.\n");
    return DAMN_GIRL;
  }
  
  read_file_into_matrix(&field, BOARD_SIZE, BOARD_SIZE);

  // show_matrix(field, BOARD_SIZE, BOARD_SIZE);


  sf::RenderWindow window(sf::VideoMode(BOARD_SIZE, BOARD_SIZE), "Ants");

  draw_board(window, field, BOARD_SIZE);
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

  return 0;
}
  
 


    

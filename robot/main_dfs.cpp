//compile: g++ -std=c++11 main_dfs.cpp -o robotdfs robot.c -lsfml-graphics -lsfml-window -lsfml-system -O3

#include "util.h"
#include "robot.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <unistd.h>
// #include <Color.hpp>

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
      int position = i*BOARD_SIZE + j;
      if(board[j][i]==5)
      {
        rectangle.setFillColor(brown);
        if (visited[position]==1)
        {
          rectangle.setFillColor(dark_brown);
        }
        windowRef.draw(rectangle);
      }
      else if (board[j][i]==10)
      {
        rectangle.setFillColor(blue);
        if (visited[position]==1)
        {
          rectangle.setFillColor(dark_blue);
        }
        windowRef.draw(rectangle);
      }
      else if (board[j][i]==15)
      {
        rectangle.setFillColor(red);
        if (visited[position]==1)
        {
          rectangle.setFillColor(dark_red);
        }
        windowRef.draw(rectangle);
      }
      else if (board[j][i]==1)
      {
        rectangle.setFillColor(green);
        if (visited[position]==1)
        {
          rectangle.setFillColor(dark_green);
        }
        windowRef.draw(rectangle);
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

void get_number_of_neighbors(Area robot_pos, int *n_neighbors)
{
  if  ( ((robot_pos.pos == 0)) || 
        ((robot_pos.pos + BOARD_SIZE  == BOARD_SIZE * BOARD_SIZE)) ||
        (robot_pos.pos == BOARD_SIZE * BOARD_SIZE - 1) ||
        (robot_pos.pos == BOARD_SIZE - 1)
      )
  {
    *n_neighbors = 2; // if position 0 0 or last line first column or the last position or last column first line.
  }
  else if ( (((robot_pos.pos - 1) % BOARD_SIZE == BOARD_SIZE - 1) && (robot_pos.pos + BOARD_SIZE < BOARD_SIZE * BOARD_SIZE)) ||
            (robot_pos.pos + BOARD_SIZE > BOARD_SIZE * BOARD_SIZE) ||
            ((robot_pos.pos + 1) % BOARD_SIZE == 0) ||
            (robot_pos.pos - 42 < 0)
          )
  {
    *n_neighbors = 3; // if any position in the first column except the last line or any position in the last line any column or any line in the last column
  }
  else
  {
    *n_neighbors = 4;
  }
}
void get_area(int position, Area *area_dst, int **field, Area *current_position)
{
  int line = position / BOARD_SIZE;
  int column = position % BOARD_SIZE;
  Area area;

  area.value = field[line][column];
  area.pos = position;
  area.previous = current_position;
  area.neighbors = NULL;

  memcpy(area_dst, &area, sizeof(area));
}

void get_neighbors(Area **robot_pos, int **field, int *visited, int *valid_neighbors)
{
  int position = (*robot_pos)->pos;
  int neighbors_count = 0;

  if (position % BOARD_SIZE != 0 && visited[position-1] != 1) // does have left neighbor
  {
    get_area(position-1, &((*robot_pos)->neighbors[neighbors_count++]), field, *robot_pos);
    (*valid_neighbors)++;
  }
  if (position - BOARD_SIZE >= 0  && visited[position - BOARD_SIZE] != 1) // does have up neighbor
  {
    get_area(position-BOARD_SIZE, &((*robot_pos)->neighbors[neighbors_count++]), field, *robot_pos);
    (*valid_neighbors)++;
  }
  if ((position + 1 ) % BOARD_SIZE != 0  && visited[position + 1] != 1) // does have right neighbor
  {
    get_area(position+1, &((*robot_pos)->neighbors[neighbors_count++]), field, *robot_pos);
    (*valid_neighbors)++;
  }
  if (position + BOARD_SIZE < BOARD_SIZE*BOARD_SIZE  && visited[position + BOARD_SIZE] != 1) // does have down neighbor
  {
    get_area(position+BOARD_SIZE, &((*robot_pos)->neighbors[neighbors_count++]), field, *robot_pos);
    (*valid_neighbors)++;
  }
}


Area* load_data(int **field)
{
  setbuf(stdout, NULL);
  int n_neighbors = 0;
  int *visited = NULL;

  visited = (int*)calloc(BOARD_SIZE * BOARD_SIZE, sizeof(int));

  field[41][41] = 666;
  Area **queue = NULL;
  int i, queue_size = 0;
  int queue_at = 0;
  Area *current=NULL;
  Area *root = NULL;
  current = (Area*)malloc(sizeof(Area));
  current->value = field[INITIAL_POS/BOARD_SIZE][INITIAL_POS%BOARD_SIZE];
  current->pos = INITIAL_POS; 
  current->previous = NULL; 
  root = current;
  while(current->value != 666)
  {
    if (visited[current->pos] == 1)
    {
      current = (queue[queue_at++]);
      continue;
    }
    visited[current->pos] = 1;
    
    //sleep(2);
    get_number_of_neighbors(*current, &n_neighbors);

    current->neighbors = (Area*)malloc(sizeof(Area) * n_neighbors);

    int valid_neighbors = 0;
    get_neighbors(&current, field, visited, &valid_neighbors);

    n_neighbors = valid_neighbors;
    current->active_neighbors = n_neighbors;
    //robot_pos.neighbors = (Area*)realloc(robot_pos.neighbors, sizeof(Area)*n_neighbors);
    queue_size += n_neighbors;
    queue = (Area**)realloc(queue, sizeof(Area*) * queue_size);
    for (i = 0; i < n_neighbors; ++i)
    {
      queue[queue_size - n_neighbors + i] = &(current->neighbors[i]);
      //printf(">>POSITION: %d\n>>VALUE: %d\n>>PREVIOUS POSITION: %p\n", queue[queue_size - n_neighbors + i]->pos, queue[queue_size - n_neighbors + i]->value, queue[queue_size - n_neighbors + i]->previous);
      
    }
    current = (queue[queue_at++]);
  }
  return root;
}

sf::RenderWindow window(sf::VideoMode(BOARD_SIZE, BOARD_SIZE), "ROBOT");

Area* dfs(Area *root, int depth, int *visited, int **field)
{
  int i;
  Area *found = NULL;
  visited[root->pos] = 1;
  if (root->value == 666)
    return root;
  if (depth > 0)
  {
    for (i = 0; i < root->active_neighbors ; ++i)
    {
      draw_board(window, field, BOARD_SIZE, visited);
      window.display();
      sf::Event event;
      while (window.pollEvent(event))
      {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
          window.close();
          break;
        }
      }
      found = dfs(&(root->neighbors[i]), depth-1, visited, field);
      if (found != NULL)
      {
        return found;
      }
    }
  }
  return NULL;
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

  //show_matrix(field, BOARD_SIZE, BOARD_SIZE);
  int *path = NULL;

  if((path = (int*)calloc(1, sizeof(int))) == NULL)
  {
    printf("ERROR on allocate path array\n");
  }


  field[41][41] = 666;

  Area *root=NULL;

  root = load_data(field);
  // printf("%d %p\n", root->pos, root->neighbors);
  

  //printf("Position: %d\nValue: %d\nActive neighbors: %d\nPrevious: %p\n", root->pos, root->value, root->previous->active_neighbors, root->previous->previous);

  Area *found = NULL;
  for (i = 0; ; ++i)
  {
    int *visited = NULL;
    visited = (int*)calloc(BOARD_SIZE*BOARD_SIZE, sizeof(int));
    found = dfs(root, i, visited, field);
    if(found != NULL)
      break;
  }
  printf(">>profundidade utilizada: %d\n", i);
  printf("Position: %d\nValue: %d\nActive neighbors: %d\nPrevious: %d\n", found->pos, found->value, found->active_neighbors, found->previous->pos);

  int cost = -666;
  while(found->previous != NULL)
  {
    cost += found->value;
    found = found->previous;
  }
  cost += found->value;
  printf(">>POSITION: %d\n>>VALUE: %d\n>>COST: %d\n", found->pos, found->value, cost);
  
  return 0;
}
  
 


    

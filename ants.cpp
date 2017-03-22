//compile: g++ -std=c++11 ants.cpp -o ants -lsfml-graphics -lsfml-window -lsfml-system

#include <iostream>
#include <tuple>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
//#include <SFML/Graphics.hpp>

using namespace std;

typedef struct
{
  int old_i, old_j, new_i, new_j;
}Position;

pair<int, int> coords[8] = {  pair<int, int>(-1, -1), pair<int, int>(-1, 0), pair<int, int>(-1, 1), pair<int, int>(0, -1), 
                              pair<int, int>(0, 1), pair<int, int>(1, -1), pair<int, int>(1, 0), pair<int, int>(1, 1)
                            };
int mod (int a, int b)
{
  if(b < 0)
    return mod(a, -b);   
  int ret = a % b;
  if(ret < 0)
    ret+=b;
  return ret;
}

class Ant 
{
  public:
    pair<int, int> position;
    bool loaded;
    int field_of_view;
    int index_in_position_array;
    Ant(pair<int, int> position, bool loaded, int field_of_view, int index_in_position_array);
    void pick_up_ant(vector<vector<int> > & board);
    void drop_off_ant(vector<vector<int> > & board);
    //vector<pair<int,int> > get_field_of_view_coords(vector<vector<int> > board);
    bool should_pick_up(vector<vector<int> > board);
    bool should_drop_off(vector<vector<int> > board);
    //int move(vector<vector<int> > board, vector<pair<int,int> > & live_ants_positions, vector<vector<int> > live_ants_board, pair<pair<int, int>, pair<int, int> > & positions);
    int move(vector<vector<int> > board, vector<vector<int> > live_ants_board, Position* positions);
};

Ant::Ant(pair<int, int> positio, bool loade, int field_of_vie, int index_in_position_arra)
{
  position = positio;
  loaded = loade;
  field_of_view = field_of_vie;
  index_in_position_array = index_in_position_arra;
}

void Ant::pick_up_ant(vector<vector<int> > & board)
{
  board[this->position.first][this->position.second] = 0;
  this->loaded = true;
}

void Ant::drop_off_ant(vector<vector<int> > & board)
{
  board[this->position.first][this->position.second] = -1;
  this->loaded = false;
}

bool Ant::should_pick_up(vector<vector<int> > board)
{
  // vector<pair<int, int> > fov_coords = this->get_field_of_view_coords(board);
  // int cont = 0;
  // for (vector<pair<int, int> >::iterator it = fov_coords.begin(); it != fov_coords.end(); ++it)
  // {
  //  if (board[it->first][it->second] == 0)
  //  {
  //    cont++;
  //  }
  // }
 //  return (((rand()%100)/100) <= cont/fov_coords.size());
  int board_lines = board.size();
  int board_columns = board[0].size();
  int cont=0;
  int total =0;
  for (int i = -this->field_of_view; i <= this->field_of_view; ++i)
  {total++;
    for (int j = -this->field_of_view; j <= this->field_of_view; ++j)
    {
      if (board[mod(this->position.first + i, board_lines)][mod(this->position.second + j, board_columns)] == 0)
        cont++;
    }
  }

  return (((random()%100)/100) <= cont/total);
}

bool Ant::should_drop_off(vector<vector<int> > board){
  // //vector<pair<int, int> > fov_coords = this->get_field_of_view_coords(board);
  // int cont = 0;
  // for (vector<pair<int, int> >::iterator it = fov_coords.begin(); it != fov_coords.end(); ++it)
  // {
  //   if (board[it->first][it->second] == -1)
  //   {
  //     cont++;
  //   }
  // }
  int board_lines = board.size();
  int board_columns = board[0].size();
  int cont=0;
  int total =0;
  for (int i = -this->field_of_view; i <= this->field_of_view; ++i)
  {total++;
    for (int j = -this->field_of_view; j <= this->field_of_view; ++j)
    {
      if (board[mod(this->position.first + i, board_lines)][mod(this->position.second + j, board_columns)] == -1)
        cont++;
    }
  }

  return (((random()%100)/100) <= cont/total);
}

// vector<pair<int,int> > Ant::get_field_of_view_coords(vector<vector<int> > board)
// {
//   int board_lines = board.size();
//   int board_columns = board[0].size();
//   vector<pair<int,int> > fov_coords;
//   for (int i = -this->field_of_view; i <= this->field_of_view; ++i)
//   {
//     for (int j = -this->field_of_view; j <= this->field_of_view; ++j)
//     {
//       fov_coords.push_back(pair<int, int>(mod(this->position.first + i, board_lines), mod(this->position.second + j, board_columns)));
//     }
//   }
//   return fov_coords;
// }

int Ant::move(vector<vector<int> > board, vector<vector<int> > live_ants_board, Position* positions)
{
    //  |0|1|2|
    //  |3|x|4|
    //  |5|6|7|
  int board_lines = board.size();
  int board_columns = board[0].size();
  int direction = random()%8;
  if (live_ants_board[mod(this->position.first + coords[direction].first, board_lines)][mod(this->position.second + coords[direction].second, board_columns)] == 1)
  {
    positions->new_i = this->position.first;
    positions->new_j = this->position.second;
    positions->old_i = this->position.first;
    positions->old_j = this->position.second;
    return 0;
  }
  positions->new_i = mod(this->position.first + coords[direction].first, board_lines);
  positions->new_j = mod(this->position.second + coords[direction].second, board_columns);
  positions->old_i = this->position.first;
  positions->old_j = this->position.second;
  this->position.first = positions->new_i;
  this->position.second = positions->new_j;
  
  return 1;
}

vector<vector<int> > generate_board(int lines, int columns)
{
  vector<vector<int> > board(lines);
  for ( int i = 0 ; i < lines ; i++ )
    board[i].resize(columns);
  return board;
}

void populate_board(vector<vector<int> > & board, int n_dead_ants)
{
  int board_lines = board.size();
  int board_columns = board[0].size();
  vector<int> total_positions;
  for (int i = 0; i < board_lines*board_columns; ++i)
    total_positions.push_back(i);
  random_shuffle(total_positions.begin(), total_positions.end());
  for (int i = 0; i < n_dead_ants; ++i)
    board[total_positions[i]/board_columns][total_positions[i]%board_columns] = -1;
  return;
}

void populate_live_ants_board(vector<vector<int> > & board, vector<Ant> live_ants)
{
  for (vector<Ant>::iterator i = live_ants.begin(); i != live_ants.end(); ++i)
  {
    board[i->position.first][i->position.second] = 1;
  }
}

vector<Ant> generate_live_ants(vector<vector<int> > board, int fov_range, int n_live_ants)
{
  vector<Ant> live_ants;
  int board_lines = board.size();
  int board_columns = board[0].size();
  vector<int> total_positions;
  for (int i = 0; i < board_lines*board_columns; ++i)
    total_positions.push_back(i);
  random_shuffle(total_positions.begin(), total_positions.end());
  for (int i = 0; i < n_live_ants; ++i)
  {
    Ant ant(pair<int, int>(total_positions[i]/board_columns,total_positions[i]%board_columns), false, fov_range, i); 
    live_ants.push_back(ant);
  }
  return live_ants;
}

// void show_board(vector<vector<int> > board)
// {
//   for (int i = 0; i < board.size(); ++i)
//   {  
//     for (int j = 0; j < board[0].size(); ++j)
//     {
//       cout << board[i][j] << '\t';
//     }
//     cout << '\n';
//   }
//   return;
// }

// void draw_board(sf::RenderWindow & windowRef, vector<vector<int> > board, vector<vector<int> > live_ants_board)
// {
//   int board_lines = board.size();
//   int board_columns = board[0].size();
//   windowRef.clear(sf::Color::White);
//   for (int i = 0; i < board_lines; ++i)
//   {
//     for (int j = 0; j < board_columns; ++j)
//     {
//       sf::RectangleShape rectangle;
//       rectangle.setSize(sf::Vector2f(1, 1));
//       rectangle.setPosition(i, j);
//       if(board[i][j]==-1)
//       {
//         rectangle.setFillColor(sf::Color::Red);
//         windowRef.draw(rectangle);
//       }
//       if (live_ants_board[i][j]==1)
//       {
//         rectangle.setFillColor(sf::Color::Black);
//         windowRef.draw(rectangle);
//       }
      
//     }
//   }
// }

int main () {
  
  srand(time(NULL));

  //sf::RenderWindow window(sf::VideoMode(160, 160), "Ants");

  vector<vector<int> > board = generate_board(160,160);
  vector<vector<int> > live_ants_board = board;
  populate_board(board, 7000);

  vector<Ant> live_ants = generate_live_ants(board, 3, 100);
  populate_live_ants_board(live_ants_board, live_ants);
  //pair<pair<int, int>, pair<int, int> > positions;
  Position positions;
  int i = 0;
  while(i<=2000)
  {
    // if (i%100==0)
    // {
    //   draw_board(window, board, live_ants_board);
    //   window.display();
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
    //cout << i << '\n';
    for (vector<Ant>::iterator ant = live_ants.begin(); ant != live_ants.end(); ++ant)
    {
      if (!ant->loaded)
      {
        if (board[ant->position.first][ant->position.second] == -1 && ant->should_pick_up(board))
        {
          ant->pick_up_ant(board);
        }
      } 
      else if (ant->loaded)
      {
        if (board[ant->position.first][ant->position.second] == 0 && ant->should_drop_off(board))
        {
          ant->drop_off_ant(board);
        }
      }
      ant->move(board, live_ants_board, &positions);
      live_ants_board[positions.old_i][positions.old_j] = 0;
      live_ants_board[positions.new_i][positions.new_j] = 1;
    }
    i++;
  }

  return 0;
}

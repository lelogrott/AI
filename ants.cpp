#include <iostream>
#include <tuple>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>

using namespace std;

class Ant 
{
  pair<int, int> position;
  bool loaded;
  int field_of_view;
  int index_in_position_array;
  public:
  	Ant(pair<int, int> position, bool loaded, int field_of_view, int index_in_position_array);
    void pick_up_ant(vector<vector<int> > & board);
    void drop_off_ant(vector<vector<int> > & board);
    vector<pair<int,int> > get_field_of_view_coords(vector<vector<int> > board);
    bool should_pick_up(vector<vector<int> > board);
    bool should_drop_off(vector<vector<int> > board);
    pair<pair<int, int>, pair<int,int> > move(vector<vector<int> > board, vector<pair<int,int> > & live_ants_positions);
};

Ant::Ant(pair<int, int> position, bool loaded, int field_of_view, int index_in_position_array)
{
	position = position;
	loaded = loaded;
	field_of_view = field_of_view;
	index_in_position_array = index_in_position_array;
}

void Ant::pick_up_ant(vector<vector<int> > & board)
{
	board[this->position.first][this->position.second] = 0;
	this->loaded = true;
}

void Ant::drop_off_ant(vector<vector<int> > & board)
{
	board[this->position.second][this->position.first] = -1;
	this->loaded = false;
}

bool Ant::should_pick_up(vector<vector<int> > board)
{
	vector<pair<int, int> > fov_coords = this->get_field_of_view_coords(board);
	int cont = 0;
	for (vector<pair<int, int> >::iterator it = fov_coords.begin(); it != fov_coords.end(); ++it)
	{
		if (board[it->first][it->second] == 0)
		{
			cont++;
		}
	}
  return (((rand()%100)/100) <= cont/fov_coords.size());
}

bool Ant::should_drop_off(vector<vector<int> > board){
  vector<pair<int, int> > fov_coords = this->get_field_of_view_coords(board);
  int cont = 0;
  for (vector<pair<int, int> >::iterator it = fov_coords.begin(); it != fov_coords.end(); ++it)
  {
    if (board[it->first][it->second] == -1)
    {
      cont++;
    }
  }
  return (((rand()%100)/100) <= cont/fov_coords.size());
}

vector<pair<int,int> > Ant::get_field_of_view_coords(vector<vector<int> > board)
{
	int board_lines = board.size();
  int board_columns = board[0].size();
	vector<pair<int,int> > fov_coords;
	for (int i = -this->field_of_view; i <= this->field_of_view; ++i)
	{
		for (int j = -this->field_of_view; j < this->field_of_view; ++j)
		{
			fov_coords.push_back(pair<int, int>((this->position.first + i)%board_lines,(this->position.second + j)%board_columns));
		}
	}
	return fov_coords;
}

pair<pair<int, int>, pair<int,int> > Ant::move(vector<vector<int> > board, vector<pair<int,int> > & live_ants_positions)
{
    //  |0|1|2|
    //  |3|x|4|
    //  |5|6|7|
  int board_lines = board.size();
  int board_columns = board[0].size();
  pair<int, int> coords[8] = {  make_pair(-1, -1), make_pair(-1, 0), make_pair(-1, 1), make_pair(0, -1), 
                                make_pair(0, 1), make_pair(1, -1), make_pair(1, 0), make_pair(1, 1)
                              };
  int direction = random()%8;
  pair<int, int> new_position = make_pair((this->position.first + coords[direction].first)%board_lines, (this->position.second + coords[direction].second)%board_columns);
  pair<int, int> old_position = this->position;
  live_ants_positions[this->index_in_position_array] = new_position;
  this->position = new_position;
  
  return make_pair(old_position, new_position);
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
  cout << board_lines << ' ' << board_columns << '\n';
  vector<int> total_positions;
  for (int i = 0; i < board_lines*board_columns; ++i)
    total_positions.push_back(i);
  random_shuffle(total_positions.begin(), total_positions.end());
  for (int i = 0; i < n_dead_ants; ++i)
    board[total_positions[i]/board_columns][total_positions[i]%board_columns] = -1;
  return;
}

vector<Ant> generate_live_ants(vector<vector<int> > board, int fov_range, int n_live_ants)
{
  vector<Ant> live_ants;
  int board_lines = board.size();
  int board_columns = board[0].size();
  vector<int> total_positions;
  for (int i = 0; i < board_lines*board_columns; ++i)
    total_positions.push_back(i);
  for (int i = 0; i < n_live_ants; ++i)
  {
    Ant ant(make_pair(total_positions[i]/board_columns,total_positions[i]%board_columns), false, fov_range, i); 
    live_ants.push_back(ant);
  }
  return live_ants;
}

int main () {
  
  srand(time(NULL));

  vector<vector<int> > board = generate_board(5,5);
  populate_board(board, 10);
  for (int i = 0; i < 5; ++i)
  {  
    for (int j = 0; j < 5; ++j)
    {
      cout << board[i][j] << '\t';
    }
    cout << '\n';
  }

  return 0;
}

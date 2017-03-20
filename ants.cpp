#include <iostream>
#include <tuple>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Ant 
{
  int line;
  int column;
  bool loaded;
  int field_of_view;
  int index_in_position_array;
  public:
  	Ant(int line, int column, bool loaded, int field_of_view, int index_in_position_array);
    void pick_up_ant(int** board);
    void drop_off_ant(int** board);
    vector<pair<int,int> > get_field_of_view_coords(int** board);
    bool should_pick_up(int** board);
    bool should_drop_off(int** board);
    pair<pair<int, int>, pair<int,int> > move(int** board, vector<pair<int,int> > live_ants_positions);
};

Ant::Ant(int line, int column, bool loaded, int field_of_view, int index_in_position_array)
{
	line = line;
	column = column;
	loaded = loaded;
	field_of_view = field_of_view;
	index_in_position_array = index_in_position_array;
}

void Ant::pick_up_ant(int** board)
{
	board[this->line][this->column] = 0;
	this->loaded = true;
}

void Ant::drop_off_ant(int** board)
{
	board[this->line][this->column] = -1;
	this->loaded = false;
}

bool Ant::should_pick_up(int** board)
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

bool Ant::should_drop_off(int **board){
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

vector<pair<int,int> > Ant::get_field_of_view_coords(int** board)
{
	int board_lines = (sizeof(board)/sizeof(board[0]));
	int board_columns = (sizeof(board)/sizeof(board[0][0]))/board_lines;
	vector<pair<int,int> > fov_coords;
	for (int i = -this->field_of_view; i <= this->field_of_view; ++i)
	{
		for (int j = -this->field_of_view; j < this->field_of_view; ++j)
		{
			fov_coords.push_back(pair<int, int>((this->line+i)%board_lines,(this->column+j)%board_columns));
		}
	}
	return fov_coords;
}

pair<pair<int, int>, pair<int,int> > Ant::move(int** board, vector<pair<int,int> > live_ants_positions)
{

}


int main () {
  
  srand(time(NULL));

  return 0;
}

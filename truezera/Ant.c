#include "Ant.h"


int generate_live_ants_array(ppAnt pp, int n_live_ants, int fov_range)
{   
  int ret = FRACASSO;
	if(((*pp)=(pAnt)malloc(sizeof(Ant)*n_live_ants))==NULL)
		ret = FRACASSO;
	else
	{	
    int i;
    int *random_numbers;
    generate_random_numbers(&random_numbers, n_live_ants);
    for (i = 0; i < n_live_ants; ++i)
    {
      (*pp)[i].position.i = random_numbers[i]/BOARD_SIZE; 
      (*pp)[i].position.j = random_numbers[i]%BOARD_SIZE;
      (*pp)[i].loaded = NAO;
      (*pp)[i].field_of_view = fov_range;
    }
    ret = SUCESSO;
	}
    return ret;
}

int show_ants_array(pAnt p, int n_ants)
{
  int i;
  for (i = 0; i < n_ants; ++i)
  {
    printf("Ant %d\n", i);
    printf("------------\n");
    printf("Position: %d, %d\n", p[i].position.i, p[i].position.j);
    printf("Loaded: %d\n", p[i].loaded);
    printf("FOV range: %d\n------------\n\n", p[i].field_of_view);
  }
  return SUCESSO;
}

int populate_board(int ***board, int n_dead_ants)
{
  int i;
  int *random_numbers;
  generate_random_numbers(&random_numbers, n_dead_ants);
  for (i = 0; i < n_dead_ants; ++i)
  {
    (*board)[random_numbers[i]/BOARD_SIZE][random_numbers[i]%BOARD_SIZE] = -1;
  }
  return SUCESSO;
}

int generate_live_ants_board(int ***board, int n_live_ants, pAnt ants_array)
{
  if (generate_board(board) == FRACASSO)
    return FRACASSO;
  int i;
  for (i = 0; i < n_live_ants; ++i)
    (*board)[ants_array[i].position.i][ants_array[i].position.j] = 1;
  return SUCESSO;
}

void pick_up_ant(int ***board, pAnt p)
{
  (*board)[p->position.i][p->position.j] = 0;
  p->loaded = SIM;
}

void drop_off_ant(int ***board, pAnt p)
{
  (*board)[p->position.i][p->position.j] = -1;
  p->loaded = NAO;
}

int should_pick_up(int **board, struct Ant ant)
{
  int cont = 0;
  int total = 0;
  int i, j;
  for (i = -ant.field_of_view; i <= ant.field_of_view; ++i)
  {
    total++;
    for (j = -ant.field_of_view; j <= ant.field_of_view; ++j)
    {
      if (board[mod(ant.position.i + i, BOARD_SIZE)][mod(ant.position.j + j, BOARD_SIZE)] == 0)
        cont++;
    }
  }
  if (((rand()%100)/100) <= (pow((cont/total),2) * 100))
    return SIM;
  else
    return NAO; 
}

int should_drop_off(int **board, struct Ant ant)
{
  int cont = 0;
  int total = 0;
  int i, j;
  for (i = -ant.field_of_view; i <= ant.field_of_view; ++i)
  {
    total++;
    for (j = -ant.field_of_view; j <= ant.field_of_view; ++j)
    {
      if (board[mod(ant.position.i + i, BOARD_SIZE)][mod(ant.position.j + j, BOARD_SIZE)] == -1)
        cont++;
    }
  }
  if (((rand()%100)/100) <= (pow((cont/total),2) * 100))
    return SIM;
  else
    return NAO;
}

int move(int **board, int **live_ants_board, pPair coords, pPair old_position, pPair new_position, pAnt p)
{
  int direction = rand()%9;
  if (live_ants_board[mod(p->position.i + coords[direction].i, BOARD_SIZE)][mod(p->position.j + coords[direction].j, BOARD_SIZE)] == 1)
  {
    new_position->i = p->position.i;
    new_position->j = p->position.j;
    old_position->i = p->position.i;
    old_position->j = p->position.j;
    return NAO;
  }
  new_position->i = mod(p->position.i + coords[direction].i, BOARD_SIZE);
  new_position->j = mod(p->position.j + coords[direction].j, BOARD_SIZE);
  old_position->i = p->position.i;
  old_position->j = p->position.j;
  p->position.i = new_position->i;
  p->position.j = new_position->j;
  
  return SIM;
}


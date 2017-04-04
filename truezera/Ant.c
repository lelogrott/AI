#include "Ant.h"


int generate_live_ants_array(ppAnt pp, int n_live_ants, int fov_range, int BOARD_SIZE)
{   
  int ret = FRACASSO;
	if(((*pp)=(pAnt)malloc(sizeof(Ant)*n_live_ants))==NULL)
		ret = FRACASSO;
	else
	{	
    int i;
    int *random_numbers;
    generate_random_numbers(&random_numbers, n_live_ants, BOARD_SIZE);
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

int generate_data_array(ppData pp, int n_data, double *max_dist, int BOARD_SIZE)
{   
  int ret = FRACASSO;
	if(((*pp)=(pData)malloc(sizeof(Data)*n_data))==NULL)
		ret = FRACASSO;
	else
	{	
    int i;
    int *random_numbers;
    double max_weight = -1; double max_size = -1;
    double min_weight = 1000; double min_size = 1000;
    generate_random_numbers(&random_numbers, n_data, BOARD_SIZE);
    FILE *f = fopen("r15.txt", "r");
    for (i = 0; i < n_data; ++i)
    {
    	double size, weight;
    	int type;
    	fscanf(f, "%lf %lf %d", &size, &weight, &type);
      (*pp)[i].position.i = random_numbers[i]/BOARD_SIZE; 
      (*pp)[i].position.j = random_numbers[i]%BOARD_SIZE;
      (*pp)[i].size = size;
      (*pp)[i].weight = weight;
      (*pp)[i].type = type;
      if (min_size > size)
        min_size = size;
      if (min_weight > weight)
        min_weight = weight;
      if (max_size < size)
        max_size = size;
      if (max_weight < weight)
        max_weight = weight;
    }
    fclose(f);
    *max_dist = sqrt(pow((max_size - min_size), 2) + pow((max_weight - min_weight), 2));
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

int populate_board(int ***board, int n_dead_ants, int BOARD_SIZE)
{
  int i;
  int *random_numbers;
  generate_random_numbers(&random_numbers, n_dead_ants, BOARD_SIZE);
  for (i = 0; i < n_dead_ants; ++i)
  {
    (*board)[random_numbers[i]/BOARD_SIZE][random_numbers[i]%BOARD_SIZE] = -1;
  }
  return SUCESSO;
}

int generate_and_populate_data_board_for_calc(ppData *board, int n_data, pData data_array, int BOARD_SIZE)
{
	int ret = FRACASSO;
  int i, j;
  if (((*board)= (ppData)malloc(sizeof(pData) * BOARD_SIZE))==NULL)
    return ret;

  for (i = 0; i < BOARD_SIZE; ++i)
  {
    if (((*board)[i] = (pData)malloc(sizeof(Data) * BOARD_SIZE))==NULL)
      return ret;
  }
  for (i = 0; i < BOARD_SIZE; ++i)
  {
  	for (j = 0; j < BOARD_SIZE; ++j)
  	{
  		(*board)[i][j].type = -1;
  	}
  }
  for (i = 0; i < n_data; ++i)
  {
  	(*board)[data_array[i].position.i][data_array[i].position.j].size = data_array[i].size;
  	(*board)[data_array[i].position.i][data_array[i].position.j].weight = data_array[i].weight;
  	(*board)[data_array[i].position.i][data_array[i].position.j].type = data_array[i].type;
  }
  return SUCESSO;
}

int generate_live_ants_board(int ***board, int n_live_ants, pAnt ants_array, int BOARD_SIZE)
{
  if (generate_board(board, BOARD_SIZE) == FRACASSO)
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

int should_pick_up(int **board, struct Ant ant, int BOARD_SIZE)
{
  double cont = 0;
  double total = 0;
  int i, j;
  for (i = -ant.field_of_view; i <= ant.field_of_view; ++i)
  {
    for (j = -ant.field_of_view; j <= ant.field_of_view; ++j)
    {
      if (board[mod(ant.position.i + i, BOARD_SIZE)][mod(ant.position.j + j, BOARD_SIZE)] == 0)
        cont++;
      total++;
    }
  }
  if (((double)(rand()%100)/100) <= pow((cont/total), 2))
    return SIM;
  else
    return NAO; 
}

int should_drop_off(int **board, struct Ant ant, int BOARD_SIZE)
{
  double cont = 0;
  double total = 0;
  int i, j;
  for (i = -ant.field_of_view; i <= ant.field_of_view; ++i)
  {
    for (j = -ant.field_of_view; j <= ant.field_of_view; ++j)
    {
      if (board[mod(ant.position.i + i, BOARD_SIZE)][mod(ant.position.j + j, BOARD_SIZE)] == -1)
        cont++;
      total++;
    }
  }

  if (((double)(rand()%100)/100.0) <= pow((cont/total), 2))
    return SIM;
  else
    return NAO;
}

// para arquivo com 400 dados:
// raio 1:
//   alpha = 0.6;
//   k1 = 0.1;
//   k2 = 0.3;
// raio 3:
//   alpha = 0.2;
//   k1 = 0.05;
//   k2 = 0.4;
// raio 5:
//   alpha = 0.7/0.4;
//   k1 = 0.01;
//   k2 = 0.6;
// para arquivo com 600 dados:
// raio 1:
//   alpha = 0.05/0.1;
//   k1 = 0.05;
//   k2 = 0.4;
// raio 2:
//   alpha = 0.05/0.1;
//   k1 = 0.05;
//   k2 = 0.8;
// raio 3:
//   alpha = ;
//   k1 = ;
//   k2 = ;
int should_pick_up_data(ppData board, struct Ant ant, double max_dist, int BOARD_SIZE)
{
  double sum = 0;
  double alpha = 0.03;
  double f_i = 0;
  int i, j, s = 0;
  Data data;
  double dist;
  for (i = -ant.field_of_view; i <= ant.field_of_view; ++i)
  {
    for (j = -ant.field_of_view; j <= ant.field_of_view; ++j)
    {
      data = board[mod(ant.position.i + i, BOARD_SIZE)][mod(ant.position.j + j, BOARD_SIZE)];
      if (data.type != -1)
      {
        s++;
        dist = (euclidean_distance(data, board[ant.position.i][ant.position.j]))/max_dist;
        sum +=  1 - dist/alpha;
      }
    }
  }
  f_i = (1.0/pow(ant.field_of_view*2 + 1, 2)) * sum;
  if (f_i < 0)
  {
    f_i = 0;
  }
  double pick = pow((0.6/(0.6 + f_i)), 2);
  double pick_chance = ((double)(rand()%1000000)/1000000);

  if ( pick_chance <= pick)
    return SIM;
  else
    return NAO;  
}

int should_drop_off_data(ppData board, struct Ant ant, double max_dist, int BOARD_SIZE)
{
  double sum = 0;
  double alpha = 0.2;
  double f_i = 0;
  int i, j, s = 0;
  Data data;
  double dist;
  for (i = -ant.field_of_view; i <= ant.field_of_view; ++i)
  {
    for (j = -ant.field_of_view; j <= ant.field_of_view; ++j)
    {
      data = board[mod(ant.position.i + i, BOARD_SIZE)][mod(ant.position.j + j, BOARD_SIZE)];
      if (data.type != -1)
      {
        s++;
        dist = (euclidean_distance(data, ant.data))/max_dist;
        sum += 1 - dist/alpha;
      }
    }
  }
  f_i = (1.0/pow(ant.field_of_view*2 + 1, 2)) * sum;
  if (f_i < 0)
  {
    f_i = 0;
  }
  double drop = pow((f_i/(0.99 + f_i)), 2);
  //drop = (exp(-pow(drop, 2)) - 1)/exp(1);
  if (((double)(rand()%1000000)/1000000) <= drop)
    return SIM;
  else
    return NAO;  
}


void pick_up_data(ppData *board, pAnt p)
{
  memcpy(&(p->data), &((*board)[p->position.i][p->position.j]), sizeof(Data));
  (*board)[p->position.i][p->position.j].type = -1;
  p->loaded = SIM;
}

void drop_off_data(ppData *board, pAnt p)
{
  memcpy(&((*board)[p->position.i][p->position.j]), &(p->data), sizeof(Data));
  p->loaded = NAO;
}

int move(int **live_ants_board, pPair coords, pPair old_position, pPair new_position, pAnt p, int BOARD_SIZE)
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


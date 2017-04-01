#include "Ant.h"

int generate_coords(Pair **pp)
{
  int ret = FRACASSO;
  if(((*pp) = (Pair*)malloc(sizeof(Pair)*9))==NULL)
    return ret;
  else
  {
    int i, j, cont = 0;
    for (i = -1; i <= 1; ++i)
    {
      for (j = -1; j <= 1; ++j)
      {
        (*pp)[cont].i = i;
        (*pp)[cont].j = j;
        cont++;
      }
    }
    ret = SUCESSO;
  }
  return ret;
}

int generate_random_numbers(int **random_numbers, int n_numbers, int BOARD_SIZE)
{
  int ret = FRACASSO;
  int* checker;
  if ((checker = (int*)calloc(BOARD_SIZE*BOARD_SIZE, sizeof(int)))==NULL)
    return ret;
  if (((*random_numbers) = (int*)calloc(n_numbers, sizeof(int)))==NULL)
    return ret;
  else
    ret = SUCESSO;
  int i, rand_number;
  for (i = 0; i < n_numbers; ++i)
  {
    rand_number = rand()%(BOARD_SIZE*BOARD_SIZE);
    if(checker[rand_number]==1)
    {  
      i--;
    } 
    else
    {
      (*random_numbers)[i] = rand_number;
      checker[rand_number] = 1;
    }
  }
  free(checker);
  return ret;
}

int generate_board(int ***board, int BOARD_SIZE)
{
  int i, ret = FRACASSO;
  if (((*board)= (int**)calloc(BOARD_SIZE, sizeof(int*)))==NULL)
    return ret;

  for (i = 0; i < BOARD_SIZE; ++i)
  {
    if (((*board)[i] = (int*)calloc(BOARD_SIZE, sizeof(int)))==NULL)
      return ret;
  }
  return SUCESSO;
}

int show_board(int **board, char *board_name, int BOARD_SIZE)
{
  int i,j;
  printf("%s\n------------------\n", board_name);
  for (i = 0; i < BOARD_SIZE; ++i)
  {
    for (j = 0; j < BOARD_SIZE; ++j)
    {
      printf("%3d", board[i][j]);
    }
    printf("\n");
  }
  return SUCESSO;
}

int mod (int a, int b)
{
  if(b < 0)
    return mod(a, -b);   
  int ret = a % b;
  if(ret < 0)
    ret+=b;
  return ret;
}

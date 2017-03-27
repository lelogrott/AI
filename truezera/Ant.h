#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define FRACASSO 0
#define SUCESSO 1

#define NAO 0
#define SIM 1

#define BOARD_SIZE 160
#define N_LIVE_ANTS 100
#define N_DEAD_ANTS 7000
#define FOV_RANGE 5

typedef struct Pair
{
  int i,j;
}Pair;

typedef struct Ant
{ 
  Pair position;
  int loaded;
  int field_of_view;
}Ant;

typedef struct Data
{ 
  Pair position;
  int type;
  double size;
  double weight;
}Data;

typedef struct Ant *pAnt, **ppAnt;
typedef struct Pair *pPair, **ppPair;
typedef struct Data *pData, **ppData;


int generate_live_ants_array(ppAnt pp, int n_live_ants, int fov_range);
int show_ants_array(pAnt p, int n_ants);
int populate_board(int ***board, int n_dead_ants);
int generate_live_ants_board(int ***board, int n_live_ants, pAnt ants_array);
void pick_up_ant(int ***board, pAnt p);
void drop_off_ant(int ***board, pAnt p);
int should_pick_up(int **board, struct Ant ant);
int should_drop_off(int **board, struct Ant ant);
int move(int **board, int **live_ants_board, pPair coords, pPair old_position, pPair new_position, pAnt p);


int generate_data_board_for_plot(int ***board, int n_data, pData data_array);
int generate_and_populate_data_board_for_calc(ppData *board, int n_data, pData data_array);
int generate_data_array(ppData pp, int n_data);

/**     UTILS FUNCTIONS     **/
int generate_coords(ppPair pp);
int generate_random_numbers(int **random_numbers, int n_numbers);
int generate_board(int ***board);
int show_board(int **board, char *board_name);
int mod (int a, int b);

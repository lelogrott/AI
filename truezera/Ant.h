#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define FRACASSO 0
#define SUCESSO 1

#define NAO 0
#define SIM 1

typedef struct Pair
{
  int i,j;
}Pair;

typedef struct Data
{ 
  Pair position;
  int type;
  double size;
  double weight;
}Data;

typedef struct Ant
{ 
  Pair position;
  int loaded;
  int field_of_view;
  Data data;
}Ant;

typedef struct Ant *pAnt, **ppAnt;
typedef struct Pair *pPair, **ppPair;
typedef struct Data *pData, **ppData;


int generate_live_ants_array(ppAnt pp, int n_live_ants, int fov_range, int BOARD_SIZE);
int show_ants_array(pAnt p, int n_ants);
int populate_board(int ***board, int n_dead_ants, int BOARD_SIZE);
int generate_live_ants_board(int ***board, int n_live_ants, pAnt ants_array, int BOARD_SIZE);
void pick_up_ant(int ***board, pAnt p);
void drop_off_ant(int ***board, pAnt p);
int should_pick_up(int **board, struct Ant ant, int BOARD_SIZE);
int should_drop_off(int **board, struct Ant ant, int BOARD_SIZE);
int should_pick_up_data(ppData board, struct Ant ant, double max_dist, int BOARD_SIZE);
int should_drop_off_data(ppData board, struct Ant ant, double max_dist, int BOARD_SIZE);
void pick_up_data(ppData *board, pAnt p);
void drop_off_data(ppData *board, pAnt p);
int move(int **live_ants_board, pPair coords, pPair old_position, pPair new_position, pAnt p, int BOARD_SIZE);


int generate_data_board_for_plot(int ***board, int n_data, pData data_array, int BOARD_SIZE);
int generate_and_populate_data_board_for_calc(ppData *board, int n_data, pData data_array, int BOARD_SIZE);
int generate_data_array(ppData pp, int n_data, double *max_dist, int BOARD_SIZE);

/**     UTILS FUNCTIONS     **/
int generate_coords(ppPair pp);
int generate_random_numbers(int **random_numbers, int n_numbers, int BOARD_SIZE);
int generate_board(int ***board, int BOARD_SIZE);
int show_board(int **board, char *board_name, int BOARD_SIZE);
int mod (int a, int b);
double euclidean_distance(Data a, Data b);


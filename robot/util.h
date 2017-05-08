#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define GOOD_TO_GO 1
#define DAMN_GIRL 0
#define BOARD_SIZE 42
#define INITIAL_POS 0
#define INF 1000000000
//0 -> solido (1)
//1 -> montanha (5) 
//2 -> patano (10)
//3 -> fogo (15)

typedef struct Area 
{
	int value = 0;
	int pos= 0;
	int active_neighbors = 0;
	Area *previous = NULL;
	Area *neighbors = NULL;
}Area;


void read_file_into_matrix(int ***matriz, int linha, int coluna)
{
	int terreno, i = 0;
	FILE *fp = fopen("data.txt", "r");
	while(fscanf(fp, "%d ", &terreno)!=EOF)
	{	
		switch(terreno){
			case 0:
				terreno = 1;
				break;
			case 1:
				terreno = 5;
				break;
			case 2:
				terreno = 10;
				break;
			case 3:
				terreno = 15;
				break;
		}
		(*matriz)[i/linha][i%coluna] = terreno;
		i++;
	}
	fclose(fp);
}

int allocate(int ***matrix, int lines, int columns)
{
	int i, j, ret = DAMN_GIRL;
	if (((*matrix) = (int**)malloc(sizeof(int*)*lines)) == NULL)
		return ret;
	for (i = 0; i < lines; ++i)
	{
		if (((*matrix)[i] = (int*)calloc(columns, sizeof(int))) == NULL)
			return ret;
	}
	ret = GOOD_TO_GO;
	return ret;
}

void show_matrix(int **matrix, int lines, int columns)
{
	int i, j;
	for (i = 0; i < lines; ++i)
	{
		for (j = 0; j < columns; ++j)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

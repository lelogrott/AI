#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GOOD_TO_GO 1
#define DAMN_GIRL 0
#define BOARD_SIZE 42
//0 -> solido (1)
//1 -> montanha (5) 
//2 -> patano (10)
//3 -> fogo (15)

void read_file_into_matrix(int ***matriz, int linha, int coluna)
{
	int terreno, i = 0;
	FILE *fp = fopen("data.txt", "r");
	while(fscanf(fp, "%d ", &terreno)!=EOF)
	{	printf("%d %d\n", i/linha, i%coluna);
		(*matriz)[i/linha][i%coluna] = terreno;
		i++;
		printf("%d\n", terreno);
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
		if (((*matrix)[i] = calloc(columns, sizeof(int))) == NULL)
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

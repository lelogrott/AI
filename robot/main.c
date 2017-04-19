#include "util.h"
#include "robot.h"

int main(int argc, char const *argv[])
{
	int **field = NULL;
	
	if (allocate(&field, 42, 42) == DAMN_GIRL)
	{
		printf("\n>>SHIIIIIT! Error on allocate.\n");
		return DAMN_GIRL;
	}
	
	read_file_into_matrix(&field, 42, 42);

	show_matrix(field, 42, 42);

	return 0;
}
	
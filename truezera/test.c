#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *f = fopen("r15.txt", "r");
	double size, weight;
	int type;
  char offset[5];

	while((fscanf(f, "%lf %lf %d", &size, &weight, &type))!= EOF)
		printf("%lf %lf %d\n", size, weight, type);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *f = fopen("data.txt", "r");
	double size, weight;
	int type;

	while((fscanf(f, "%lf %lf %d", &size, &weight, &type))!= EOF)
		printf("%lf %lf %d\n", size, weight, type);
	return 0;
}
#include "mementry.h"

int main(int argc, char *argv[])
{
	char *a = (char *) malloc(4500);
	char *b = (char *) malloc(50);
	char *c = (char *) malloc(50);

	free(a);
	free(b);
	free(b);
	char *d = (char *) malloc(4550);
	char *e = (char *) malloc(50);
	free(b);
	char *f = (char *) malloc(168);
	free(e);

	int x = 3;
	int *z = &x;
	free(z);

	int *g = (int *) malloc(208);

	printf("\n");
	return 0;
}

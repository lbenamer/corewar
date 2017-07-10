#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	char *var = "ol";

	printf("size of var = %lu\n", sizeof(var));

	return 0;
}
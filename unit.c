#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	int val;

	val = atoi(argv[1]);

	int a = val;
	int b = val;

	a &= 0x0fff;
	b %= 4096;

	printf("a = %d\n", a);
	printf("b = %d\n", b);

	return 0;
}
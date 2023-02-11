#include "malloc.h"
//#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	for (int i = 0 ; i < 9999 ; i++)
	{
		char *s = malloc(10);
		if (!s)
			return 1;
		s[0] = 'c';
		s[1] = 'h';
		s[2] = 'a';
		s[3] = 'r';
		s[4] = 'l';
		s[5] = 'e';
		s[6] = 's';
		s[7] = 'b';
		s[8] = 'e';
		s[9] = '\0';
		//printf("%s\n", s);
	}
	return 0;
}

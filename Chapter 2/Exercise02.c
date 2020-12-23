#include <stdio.h>

int main()
{
	int i, c, lim;

	for (i = 0;   ((i < lim - 1) 
			    + ((c = getchar()) != '\n') 
			    + (c != EOF)) 
	/*--------------------------------------*/
			    == 3; ++i)
	{
		/* ... */
	}

	return 0;
}

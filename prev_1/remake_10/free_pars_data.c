#include "my_fdf.h"

void	free_parse_data(int ***data, int elements, int lines)
{
	int	thrd;
	int	scnd;
	int	frst;

	thrd = 0;
	frst = 0;
	scnd = 0;
	while (thrd < 2)
	{
		while (scnd < lines)
		{
			free(data[thrd][scnd]);
			scnd++;
		}
			free(data[thrd]);
			scnd = 0;
			thrd++;
	}
	//free(data[2]); // free NULL 3rd dim
	free(data);
}

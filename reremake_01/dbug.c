#include "my_fdf.h"

void db_point(t_mlx_ptrs *mlx_ptrs)
{
	t_point	**point_arr;
	int	i;
	int j;

	i = 0;
	point_arr = mlx_ptrs->prs_data->point;
	while(i < mlx_ptrs->prs_data->vert)
	{
		j = 0;
		printf("line %2d: ", i);
		while(j < mlx_ptrs->prs_data->horiz)
		{
//			printf("%d", point_arr[i][j].x);
//			printf("%d", point_arr[i][j].y);
			printf("%2d, ", point_arr[i][j].z);
			printf("%d | ", point_arr[i][j].color);
			j++;
		}
		printf("\n");
		i++;
	}
		printf("\n");
}

void db_point_xy(t_mlx_ptrs *mlx_ptrs)
{
	t_point	**point_arr;
	int	i;
	int j;

	i = 0;
	point_arr = mlx_ptrs->prs_data->point;
	while(i < mlx_ptrs->prs_data->vert)
	{
		j = 0;
		printf("line %2d: ", i);
		while(j < mlx_ptrs->prs_data->horiz)
		{
			printf("%2d, ", point_arr[i][j].x);
			printf("%d | ", point_arr[i][j].y);
			j++;
		}
		printf("\n");
		i++;
	}
		printf("\n");
}

void db_point_xy_prs_data(t_prs_data *prs_data)
{
	t_point	**point_arr;
	int	i;
	int j;

	i = 0;
	point_arr = prs_data->point;
	while(i < prs_data->vert)
	{
		j = 0;
		printf("line %2d: ", i);
		while(j < prs_data->horiz)
		{
			printf("%2d, ", point_arr[i][j].x);
			printf("%d | ", point_arr[i][j].y);
			j++;
		}
		printf("\n");
		i++;
	}
		printf("\n");
}


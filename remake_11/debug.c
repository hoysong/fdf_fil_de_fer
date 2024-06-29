#include "my_fdf.h"

void debug_lkd_list(t_dnode *gnl_node)
{
	printf("=== debug lkd_list ===\n");
	//gnl_node = gnl_node->next_node;
	while (gnl_node->data != NULL)
	{
		printf("%s", (char *)gnl_node->data);
		gnl_node = gnl_node->next_node;
	}
	printf("\n");
}

void debug_splits(char ***splits)
{
	int	two_dim = 0;
	int	one_dim = 0;
	printf("=== debug splits ===\n");
	while ((*splits))
	{
		while((*splits)[two_dim])
		{
			printf("%s", (*splits)[two_dim]);
			printf(" ");
			two_dim++;
		}
		two_dim = 0;
		splits++;
	}
	printf("\n");
}

void debug_parsed_data(int ***parsed_data, int elements, int lines)
{
	int	x = 0;
	int	y = 0;

	printf("=== debug parsed data(height) ===\n");

	while (y < lines)
	{
		while(x < elements)
		{
			printf("%3d", parsed_data[0][y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	y = 0;

	printf("=== debug parsed data(color) ===\n");
	parsed_data++;

	while (y < lines)
	{
		while(x < elements)
		{
			printf("%X ", parsed_data[0][y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

void	debug_point_arr(t_mlx_ptrs *mlx_ptrs)
{
	t_point	**point_arr;
	int	height;
	int	width;

	height = 0;
	width = 0;
	point_arr = mlx_ptrs->data->point;
	printf("========= print point_arr =========\n");
	while(height < mlx_ptrs->data->vert)
	{
		while(width < mlx_ptrs->data->horiz)
		{
			printf("%d", point_arr[height][width].x);
			width ++;
		}
		printf("\n");
		width = 0;
		height++;
	}
}

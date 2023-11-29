#include <stdio.h>
#include "cub3d.h"

int	fill_map(char **map, t_vars *vars)
{
	int	x;
	int	y;

	x = vars->start_x;
	y = vars->start_y;
	if (map[y][x] == '0' || map[y][x] == 'X')
		map[y][x] = '2';
	
}


int flood_fill(t_vars *vars)
{
	char	**copy;
	int		i;

	//create map copy
	copy = (char **)malloc(sizeof(char *) * (vars->height + 1));
	i = 0;
	while (i < vars->height)
	{
		copy[i] = (char *)malloc(sizeof(char) * (vars->width + 1));
		if (!copy[i])
		{
			//free_map(copy);
			exit_error("ERROR - Malloc Error");
		}
		i++;
	}
	//copy contents to map copy
	i = 0;
	while (i < vars->height)
	{
		copy[i] = vars->map[i];
		i++;
	}
	printf("+++++++++++++++++++++++++++++++\n");
	printf("copy copied map\n");
	print_maps(copy, vars);


	//flood fill
		//fail ==> free, exit
	if (fill_map(copy, vars) == 1)
	{
		//free map
		return (1);
	}
	//free map
	//success ==> free
	return (0);
}
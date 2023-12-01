#include <stdio.h>
#include "cub3d.h"

void	exit_error(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

void	print_maps(char **map, t_vars *vars)
{
	int	i;
	int	j;

	printf("--------------------------------------------\n");
	printf("starting print_maps function\n");
	i = 0;
	while (map[i] && i < vars->height - 1)
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n--------------------------------------------\n\n");
}

int	get_array_size(char **array)
{
	int	count;

	while (array[count])
	{
		count++;
	}
	printf("array size: %d\n", count);
	return (count);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	//array = NULL;//
}

void	free_map(char **map, int max)
{
	int	i;

	i = 0;
	while (map[i] && map[i][0] && i < max)
	{
		free(map[i]);
		i++;
	}
	free(map);
	//map = NULL;//
}

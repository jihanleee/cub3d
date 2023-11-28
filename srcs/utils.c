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
	while (map[i] && i < vars->height)
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
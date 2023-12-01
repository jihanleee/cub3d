
#include <stdio.h>
#include "cub3d.h"

static int	map_content(t_vars *vars)
{
	char	**map;
	int		x;
	int		y;

	map = vars->first_map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
			{
				vars->players = vars->players + 1;
				vars->start_x = x;
				vars->start_y = y;
			}
			else if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != ' ' && map[y][x] != '\n')
				return (1);
			x++;
		}
		y++;
	}
	if (vars->players != 1)
		return (1);
	return (0);
}

char	*get_map_line(char *str, t_vars *vars)
{
	char	*new_string;
	int		i;

	new_string = (char *)malloc(sizeof(char) * (vars->width));
	if (!new_string)
	{
		free(new_string);
		//error message?
	}
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ' ')
			new_string[i] = '1'; //'X'
		else
			new_string[i] = str[i];
		i++;
	}
	while (i < vars->width - 1)
	{
		new_string[i] = '1'; //'X'
		i++;
	}
	new_string[i] = '\0';
	//printf("new line: %s\n", new_string);
	return (new_string);
}

void	parse_map(t_vars *vars)
{
	int	count;
	char	*line;

	vars->map = (char **)malloc(sizeof(char *) * (vars->height + 1));
	if (!vars->map)
	{
		free(vars->map);
		exit_error("ERROR - Map Allocation Failed");
	}
	count = 0;
	while (vars->first_map[count])
	{
		line = get_map_line(vars->first_map[count], vars);
		vars->map[count] = line;
		count++;
	}
}

int	vertical_walls(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->height)
	{
		if (vars->map[i][0] != '1')
			return (1);
		i++;
	}
	j = 0;
	while (j < vars->height)
	{
		if (vars->map[j][vars->width - 2] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	horizontal_walls(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[0][i])
	{
		if (vars->map[0][i] != '1')
			return (1);
		i++;
	}
	j = 0;
	while (vars->map[vars->height - 1][j])
	{
		if (vars->map[vars->height - 1][j] != '1')
		{
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_borders(t_vars *vars)
{
	if (vertical_walls(vars) == 1 || horizontal_walls(vars) == 1)
		return (1);
	return (0);
}


int	validate_map(t_vars *vars)
{
	//check if all characters are valid
	//0, 1, N, S, E, or W
	if (map_content(vars) == 1)
		return (1);
	//change spaces to X
	parse_map(vars);
	print_maps(vars->map, vars);
	//check if the borders are all walls
	if (check_borders(vars) == 1)
		return (1);
	return (0);
}
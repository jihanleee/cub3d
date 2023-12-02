
#include <stdio.h>
#include "cub3d.h"


void	save_player_info(t_vars *vars, char c, int x, int y)
{
	vars->players = vars->players + 1;
	vars->player_x = x;
	vars->player_y = y;
	if (c == 'N')
		vars->player_dir = NORTH;
	else if (c == 'S')
		vars->player_dir = SOUTH;
	else if (c == 'E')
		vars->player_dir = WEST;
	else if (c == 'W')
		vars->player_dir = EAST;
	printf("direction: %d\n", vars->player_dir);
}
int	map_content(t_vars *vars)
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
				save_player_info(vars, map[y][x], x, y);
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

	new_string = (char *)ft_calloc(sizeof(char), (vars->width));
	if (!new_string)
		free(new_string);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ' ')
			new_string[i] = '1';
		else
			new_string[i] = str[i];
		i++;
	}
	while (i < vars->width - 1)
	{
		new_string[i] = '1';
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

void	parse_map(t_vars *vars)
{
	int	count;
	char	*line;

	vars->map = (char **)ft_calloc(sizeof(char *), (vars->height + 1));
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

int	validate_map(t_vars *vars)
{
	if (map_content(vars) == 1)
		return (1);
	parse_map(vars);
	print_maps(vars->map, vars);
	if (check_borders(vars) == 1)
		return (1);
	return (0);
}

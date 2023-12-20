/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee2 <solee2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 02:48:37 by solee2            #+#    #+#             */
/*   Updated: 2023/12/20 17:19:43 by solee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

void	save_player_info(t_vars *vars, char c, int x, int y)
{
	vars->players = vars->players + 1;
	vars->player_x = x + 0.5;
	vars->player_y = y + 0.5;
	if (c == 'N')
		vars->init_dir_x = 0;
	if (c == 'N')
		vars->init_dir_y = 1;
	if (c == 'S')
		vars->init_dir_x = 0;
	if (c == 'S')
		vars->init_dir_y = -1;
	if (c == 'E')
		vars->init_dir_x = 1;
	if (c == 'E')
		vars->init_dir_y = 0;
	if (c == 'W')
		vars->init_dir_x = -1;
	if (c == 'W')
		vars->init_dir_y = 0;
	vars->dir_x = vars->init_dir_x;
	vars->dir_y = vars->init_dir_y;
	vars->plane_x = vars->init_dir_y * 0.66;
	vars->plane_y = -vars->init_dir_x * 0.66;
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
			if (map[y][x] == 'N' || map[y][x] == 'S' || \
			map[y][x] == 'E' || map[y][x] == 'W')
				save_player_info(vars, map[y][x], x, y);
			else if (map[y][x] != '1' && map[y][x] != '0' && \
			map[y][x] != ' ' && map[y][x] != '\n')
				return (free_map(vars->first_map, vars->height), 1);
			x++;
		}
		y++;
	}
	if (vars->players != 1)
		return (free_map(vars->first_map, vars->height), 1);
	return (0);
}

char	*get_map_line(char *str, t_vars *vars)
{
	char	*new_string;
	int		i;

	new_string = (char *)ft_calloc(sizeof(char), (vars->width + 1));
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
	int		count;
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
	{
		return (1);
	}
	parse_map(vars);
	if (check_borders(vars) == 1)
	{
		free_map(vars->map, vars->height);
		free_map(vars->first_map, vars->height);
		return (1);
	}
	return (0);
}

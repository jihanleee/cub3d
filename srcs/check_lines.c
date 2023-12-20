/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 02:23:20 by maya              #+#    #+#             */
/*   Updated: 2023/12/20 16:53:22 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int	line_info(t_vars *vars, char *line, int count)
{
	char	**array;
	char	*file;
	int		fd;

	array = ft_split(line, ' ');
	if (count >= 0 && count < 4)
	{
		if (line_first_word(array[0], count) == 1)
			return (free_array(array), 1);
		file = ft_strtrim(array[1], "\n");
		fd = open(file, O_RDONLY);
		free(file);
		if (fd == -1)
			return (free_array(array), 1);
	}
	else if ((count == 4 || count == 7) && line[0] != '\n')
		return (free_array(array), 1);
	else if (count == 5 || count == 6)
	{
		if (fc_value(array, count, vars) == 1)
			return (free_array(array), 1);
	}
	return (free_array(array), 0);
}

void	malloc_map(t_vars *vars, int count)
{
	vars->height = count - 8;
	if (vars->height <= 0)
		exit_error("ERROR - Map Allocation Failed");
	vars->first_map = (char **)ft_calloc(sizeof(char *), (vars->height + 1));
	if (!vars->first_map)
	{
		exit_error("ERROR - Map Allocation Failed");
	}
}

void	add_to_map(t_vars *vars, int count)
{
	int		length;
	char	*line;
	int		line_num;
	int		map_line;
	int		fd;

	malloc_map(vars, count);
	line_num = -1;
	fd = open(vars->file, O_RDONLY);
	line = get_next_line(fd);
	map_line = -1;
	while (line != NULL)
	{
		if (++line_num >= 8)
		{
			length = ft_strlen(line);
			if (length > vars->width)
				vars->width = length;
			vars->first_map[++map_line] = ft_strdup(line);
		}
		free(line);
		line = get_next_line(fd);
	}
}

int	check_lines(t_vars *vars)
{
	char	*line;
	int		count;
	int		result;
	int		fd;

	fd = open(vars->file, O_RDONLY);
	count = 0;
	result = 0;
	line = get_next_line(fd);
	if (!line)
		exit_error("ERROR - Empty File");
	while (line)
	{
		if (count < 8 && line_info(vars, line, count) == 1)
			result = 1;
		count++;
		free(line);
		line = get_next_line(fd);
	}
	if (result == 1)
		return (1);
	else
		return (add_to_map((free(line), vars), count), 0);
}

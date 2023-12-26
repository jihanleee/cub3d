/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: solee2 <solee2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 02:24:46 by maya              #+#    #+#             */
/*   Updated: 2023/12/26 16:06:22 by solee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int	hidden_file(char *s1, char *s2)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == '/')
			j = i;
		i++;
	}
	p = 0;
	j++;
	while (s1[j] && s2[p])
	{
		if (s1[j] != s2[p])
			return (0);
		j++;
		p++;
	}
	return (1);
}

int	line_first_word(char *str, int count)
{
	int	result;

	result = 1;
	if (ft_strlen(str) != 2)
		return (1);
	if (count == 0)
		result = ft_strncmp(str, "NO", 2);
	else if (count == 1)
		result = ft_strncmp(str, "SO", 2);
	else if (count == 2)
		result = ft_strncmp(str, "WE", 2);
	else if (count == 3)
		result = ft_strncmp(str, "EA", 2);
	return (result);
}

int	check_fc_char(const char *str, int count, size_t n)
{
	char	*condition;
	size_t	i;

	if (count == 5)
		condition = "F";
	if (count == 6)
		condition = "C";
	i = 0;
	while ((str[i] || condition[i]) && i < n)
	{
		if (str[i] != condition[i])
			return ((unsigned char)str[i] - (unsigned char)condition[i]);
		i++;
	}
	return (0);
}

int	fc_value(char **array, int count, t_vars *vars)
{
	char	**rgb;
	int		index;
	int		temp;

	if (ft_strlen(array[0]) != 1 || check_fc_char(array[0], count, 1) != 0)
		return (1);
	rgb = ft_split(array[1], ',');
	index = 0;
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL)
		return (free_array(rgb), 1);
	while (index < 3)
	{
		temp = ft_atoi(rgb[index]);
		if (temp < 0 || temp > 255)
			return (free_array(rgb), 1);
		index++;
	}
	if (count == 5)
		vars->f_colour = (ft_atoi(rgb[0]) << 16) + \
		(ft_atoi(rgb[1]) << 8) + (ft_atoi(rgb[2]));
	else if (count == 6)
		vars->c_colour = (ft_atoi(rgb[0]) << 16) + \
		(ft_atoi(rgb[1]) << 8) + (ft_atoi(rgb[2]));
	return (free_array(rgb), 0);
}

void	validate_file(t_vars *vars)
{
	int	fd;

	if (hidden_file(vars->file, ".cub") == 1)
		exit_error("ERROR - Hidden File");
	if (ft_strncmp(vars->file + ft_strlen(vars->file) - 4, ".cub", 4) != 0)
		exit_error("ERROR - Wrong File Extension");
	fd = open(vars->file, O_RDONLY);
	if (fd == -1)
		exit_error("ERROR - File Could Not Be Opened");
	if (check_lines(vars) == 1)
		exit_error("ERROR - File Doesn't Contain Exact Info");
}

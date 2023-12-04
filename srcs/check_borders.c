/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:59:09 by jihalee           #+#    #+#             */
/*   Updated: 2023/12/04 12:59:13 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

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

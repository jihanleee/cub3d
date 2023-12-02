/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:07:47 by jihalee           #+#    #+#             */
/*   Updated: 2023/12/02 23:07:50 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_sidedist(t_vars *vars)
{
	if (vars->rinfo.raydir_x < 0)
	{
		vars->rinfo.step_x = -1;
		vars->rinfo.sidedist_x = \
		(vars->player_x - vars->rinfo.map_x) * vars->rinfo.deltadist_x;
	}
	else
	{
		vars->rinfo.step_x = 1;
		vars->rinfo.sidedist_x = \
		(vars->rinfo.map_x + 1.0 - vars->player_x) * vars->rinfo.deltadist_x;
	}
	if (vars->rinfo.raydir_y < 0)
	{
		vars->rinfo.step_y = -1;
		vars->rinfo.sidedist_y = \
		(vars->player_y - vars->rinfo.map_y) * vars->rinfo.deltadist_y;
	}
	else
	{
		vars->rinfo.step_y = 1;
		vars->rinfo.sidedist_y = \
		(vars->rinfo.map_y + 1.0 - vars->player_y) * vars->rinfo.deltadist_y;
	}
}

void	calculate_deltadist(t_vars *vars)
{
	if (vars->rinfo.raydir_x == 0)
		vars->rinfo.deltadist_x = 9999999;
	else
		vars->rinfo.deltadist_x = fabs(1 / vars->rinfo.raydir_x);
	if (vars->rinfo.raydir_y == 0)
		vars->rinfo.deltadist_y = 9999999;
	else
		vars->rinfo.deltadist_y = fabs(1 / vars->rinfo.raydir_y);
}

void	calculate_perpwalldist(t_vars *vars)
{
	vars->rinfo.hit = 0;
	while (vars->rinfo.hit == 0)
	{
		if (vars->rinfo.sidedist_x < vars->rinfo.sidedist_y)
		{
			vars->rinfo.sidedist_x += vars->rinfo.deltadist_x;
			vars->rinfo.map_x += vars->rinfo.step_x;
			vars->rinfo.side = 0;
		}
		else
		{
			vars->rinfo.sidedist_y += vars->rinfo.deltadist_y;
			vars->rinfo. map_y += vars->rinfo.step_y;
			vars->rinfo.side = 1;
		}
		if (vars->map[vars->rinfo.map_y][vars->rinfo.map_x] == '1')
			vars->rinfo.hit = 1;
	}
	if (vars->rinfo.side == 0)
		vars->rinfo.perpwalldist = \
		(vars->rinfo.sidedist_x - vars->rinfo.deltadist_x);
	else
		vars->rinfo.perpwalldist = \
		(vars->rinfo.sidedist_y - vars->rinfo.deltadist_y);
}

void	get_dist(t_vars *vars)
{
	vars->rinfo.map_x = (int)vars->player_x;
	vars->rinfo.map_y = (int)vars->player_y;
	calculate_deltadist(vars);
	calculate_sidedist(vars);
	calculate_perpwalldist(vars);
}

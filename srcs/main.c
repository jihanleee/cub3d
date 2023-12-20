/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 02:24:58 by maya              #+#    #+#             */
/*   Updated: 2023/12/20 17:41:29 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int	initialize_vars(t_vars *vars)
{
	vars->go_u = 0;
	vars->go_d = 0;
	vars->go_l = 0;
	vars->go_r = 0;
	vars->rotate_cw = 0;
	vars->rotate_ccw = 0;
	vars->current_angle = 0;
	vars->first_map = NULL;
	vars->map = NULL;
	vars->players = 0;
	vars->height = 0;
	vars->width = 0;
	vars->f_colour = 0;
	vars->c_colour = 0;
	return (0);
}

/*closes the windown and frees all the resources used 
to terminate the program.*/
int	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->tex[0].img);
	mlx_destroy_image(vars->mlx, vars->tex[1].img);
	mlx_destroy_image(vars->mlx, vars->tex[2].img);
	mlx_destroy_image(vars->mlx, vars->tex[3].img);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free_map(vars->first_map, vars->height);
	free_map(vars->map, vars->height);
	free(vars->mlx);
	exit(0);
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	move(vars);
	rotate(vars);
	raycasting(vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
	{
		exit_error("ERROR - Invalid Number of Arguments");
		return (1);
	}
	vars.file = argv[1];
	initialize_vars(&vars);
	validate_file(&vars);
	if (validate_map(&vars) == 1)
	{
		exit_error("ERROR - Invalid Map");
		return (1);
	}
	initialize_mlx(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_hook(vars.win, 02, 1L << 0, keypress, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 03, 1L << 1, keyrelease, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

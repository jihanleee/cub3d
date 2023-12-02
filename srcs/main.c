/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maya <maya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 02:24:58 by maya              #+#    #+#             */
/*   Updated: 2023/12/03 02:25:00 by maya             ###   ########.fr       */
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
	vars->start_x = 0;
	vars->start_y = 0;
	vars->dir_x = 0;
	vars->dir_y = -1; /*initial direction*/	
	vars->plane_x = -0.66;
	vars->plane_y = 0; /*camera plane of FOV 90*/
	vars->first_map = NULL;
	vars->map = NULL;
	vars->player_x = 1.5;
	vars->player_y = 1.5;
	vars->players = 0;
	vars->height = 0;
	vars->width = 0;
	vars->f_colour = 0;
	vars->c_colour = 0;
	return (0);
}

/*closes the windown and frees all the resources used to terminate the program.*/
int	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->tex[0].img);
	mlx_destroy_image(vars->mlx, vars->tex[1].img);
	mlx_destroy_image(vars->mlx, vars->tex[2].img);
	mlx_destroy_image(vars->mlx, vars->tex[3].img);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);/* 
	free_map(vars->first_map, vars->height - 1); */
	//free_textures(&vars);
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

int	save_texture(t_vars *vars)
{
	int		index;
	char	*line;
	char	*file;
	char	**array;
	int		fd;
	int		i;
	int		j;

	index = 0;
	fd = open(vars->file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (index < 4)
		{
			array = ft_split(line, ' ');
			file = ft_strtrim(array[1], "\n");
			ft_printf("file %s\n", file);
			vars->tex[index].img = mlx_xpm_file_to_image(vars->mlx, file, &i, &j);
			vars->tex[index].addr = mlx_get_data_addr((vars->tex[index].img), \
				&(vars->tex[index].bits_per_pixel), \
				&(vars->tex[index].line_length), \
				&(vars->tex[index].endian));
			if (array[2] != 0) //array[2]
			{
				exit_error("ERROR - Invalid Line in File");
				//return (1);
			}
			free_array(array);
			free(file);
		}
		free(line);
		line = get_next_line(fd);
		index++;
	}
	free(line);
	return (0);
}	
int	main(int argc, char **argv)
{
	t_vars	vars;
/* 	int		i;
	int		j; */

	if (argc != 2)
		return (1);
	vars.file = argv[1];
	initialize_vars(&vars);
	validate_file(&vars);
	/* save_texture(&vars); */
	//free_map(vars.first_map, vars.height);
	print_maps(vars.first_map, &vars);//
	printf("f-colour: %u\n", vars.f_colour);
	printf("c-colour: %u\n", vars.c_colour);
	if (validate_map(&vars) == 1)
	{
		exit_error("ERROR - Invalid Map");
		return (1);
	}
	//print_maps(vars.map, &vars);//
	initialize_mlx(&vars);
	save_texture(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_hook(vars.win, 02, 1L << 0, keypress, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 03, 1L << 1, keyrelease, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

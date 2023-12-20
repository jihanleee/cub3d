/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:50:49 by jihalee           #+#    #+#             */
/*   Updated: 2023/12/20 16:11:03 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_error_exit(t_vars *vars, char *line, int index, int fd)
{
	while (--index >= 0)
		mlx_destroy_image(vars->mlx, vars->tex[index].img);
	free_map(vars->first_map, vars->height);
	free_map(vars->map, vars->height);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	exit_error("ERROR - Invalid Texture");
	return (0);
}

bool	is_cardinal_valid(char *line, int index)
{
	if ((index == 0 && ft_strncmp(line, "NO ", 3) == 0))
		return (1);
	if ((index == 1 && ft_strncmp(line, "SO ", 3) == 0))
		return (1);
	if ((index == 2 && ft_strncmp(line, "WE ", 3) == 0))
		return (1);
	if ((index == 3 && ft_strncmp(line, "EA ", 3) == 0))
		return (1);
	return (0);
}

bool	load_image(t_vars *vars, char *line, int index)
{
	int	w;
	int	h;

	vars->tex[index].img = \
	mlx_xpm_file_to_image(vars->mlx, ft_strchr(line, ' ') + 1, &w, &h);
	if (!vars->tex[index].img)
		return (1);
	vars->tex[index].addr = \
		mlx_get_data_addr((vars->tex[index].img), \
		&(vars->tex[index].bits_per_pixel), \
		&(vars->tex[index].line_length), \
		&(vars->tex[index].endian));
	if (w != 128 || h != 128)
	{
		mlx_destroy_image(vars->mlx, vars->tex[index].img);
		return (1);
	}
	return (0);
}

int	save_texture(t_vars *vars)
{
	int		index;
	char	*line;
	int		fd;

	index = 0;
	fd = open(vars->file, O_RDONLY);
	line = (char *)1;
	while (line && index < 4)
	{
		line = get_next_line(fd);
		if (!is_cardinal_valid(line, index))
			texture_error_exit(vars, line, index, fd);
		*(ft_strchr(line, '\n')) = '\0';
		if (load_image(vars, line, index) || vars->tex[index].img == NULL)
			texture_error_exit(vars, line, index, fd);
		free(line);
		index++;
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

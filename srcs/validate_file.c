

#include <stdio.h>
#include "cub3d.h"

static int	hidden_file(char *s1, char *s2)
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

static int	line_first_word(char *str, int count)
{
	int	result;

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
	return (0);
}

static int	fc_value(char **array, int count, t_vars *vars)
{
	char	**rgb;
	int		index;
	int		result;
	int		temp;

	if (ft_strlen(array[0]) != 1)
		return (1);
	if (count == 5)
		result = ft_strncmp("F", array[0], 1);
	else if (count == 6)
		result = ft_strncmp("C", array[0], 1);
	if (result != 0)
		return (1);
	rgb = ft_split(array[1], ',');
	index = 0;
	while (index < 3)
	{
		temp = ft_atoi(rgb[index]);
		if (temp < 0 || temp > 225)
			return (1);
		index++;
	}
	if (count == 5)
		vars->f_colour = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8) + (ft_atoi(rgb[2]));
	else if (count == 6)
		vars->c_colour = (ft_atoi(rgb[0]) << 16) + (ft_atoi(rgb[1]) << 8) + (ft_atoi(rgb[2]));
	free_array(rgb);
	return (0);
}


static int	line_info(t_vars *vars, char *line, int count)
{
	char	**array;
	char	*file;
	int		fd; //check when we add textures

	array = ft_split(line, ' ');
	if (count >= 0 && count < 4)
	{
		//printf("%d: first word of line: %s\n", count, array[0]);
		//if size of array is not 2, it returns an error
		//if (get_array_size(array) != 2)
		//	return (1);
		if (line_first_word(array[0], count) == 1)
		{
			free_array(array);
			return (1);
		}
		//check when we add textures
		file = ft_strtrim(array[1], "\n");
		printf("str: %s and file: %s\n", array[1], file);
		fd = open(file, O_RDONLY);
		free(file);
		if (fd == -1)
		{
			free_array(array);
			exit_error("ERROR - File Could Not Be Opened");
		}
	}
	else if ((count == 4 || count == 7) && line[0] != '\n')
	{
		free_array(array);
		return (1);
	}
	else if (count == 5 || count == 6) //F and C value
		if (fc_value(array, count, vars) == 1)
		{
			free_array(array);
			return (1);
		}
	free_array(array);
	return (0);
}

void	add_to_map(t_vars *vars, int count)
{
	int		length;
	int		height;
	char	*line;
	int		line_num;
	int		map_line;
	int		fd;

	height = count - 8;
	vars->height = height;
	vars->first_map = (char **)ft_calloc(sizeof(char *), (height + 1));
	if (!vars->first_map)
	{
		free(vars);
		exit_error("ERROR - Map Allocation Failed");
	}
	line_num = 0;
	fd = open(vars->file, O_RDONLY);
	if (fd == -1)
		exit_error("ERROR - File Could Not Be Opened");
	line = get_next_line(fd);
	while (line_num < 8)
	{
		line_num++;
		free(line);
		line = get_next_line(fd);
	}
	map_line = 0;
	while (line != NULL)
	{
		length = ft_strlen(line);
		if (length > vars->width)
			vars->width = length;
		/* vars->first_map[map_line] = (char *)ft_calloc(sizeof(char), (length + 1));
		if (!vars->first_map[map_line])
		{
			//free_map(vars->first_map);
			exit_error("ERROR - Malloc Error");
		} */
		/* vars->first_map[map_line] = line; //strdup? */
		vars->first_map[map_line] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		map_line++;
	}
	//free(line);
	return (0);
}

static int	check_lines(t_vars *vars)
{
	char	*line;
	int		count;
	int		fd;

	fd = open(vars->file, O_RDONLY);
	//if (fd == -1)
	//	exit_error("ERROR - File Could Not Be Opened");
	count = 0;
	line = get_next_line(fd);
	while (line != NULL  && count < 8)
	{
		//printf("%d: %s ==> %d\n", count, line, line[0]);
		if (line_info(vars, line, count) == 1)
			return (1);
		count++;
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	add_to_map(vars, count);
	return (0);
}

void	validate_file(t_vars *vars)
{
	int fd;

	if (hidden_file(vars->file, ".cub") == 1)
		exit_error("ERROR - Hidden File");
	if (ft_strncmp(vars->file + ft_strlen(vars->file) - 4, ".cub", 4) != 0)
		exit_error("ERROR - Wrong File Extension");
	fd = open(vars->file, O_RDONLY);
	if (fd == -1)
		exit_error("ERROR - File Could Not Be Opened");
	if (check_lines(vars) == 1)
		exit_error("ERROR - File Doesn't Contain Exact Info");
	printf("width: %d\n", vars->width);
	printf("height: %d\n", vars->height);
}
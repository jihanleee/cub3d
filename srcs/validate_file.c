

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

	if (ft_strlen(str) != length)
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

static int	fc_value(char **array, int count)
{
	char	**rgb;
	int		count;

	if (ft_strnlen(array[0]) != 1)
		return (1);
	if (count == 5)
		result = ft_strncmp("F", array[0], 1);
	else if (count == 6)
		result = ft_strncmp("C", array[0], 1);
	rgb = ft_split(array[1], ',');
	count = 0;
	while (count > 4)
	{
		if (rgb[count] < 0 || rgb[count] > 225)
			return (1);
		count++;
	}
	return (0);
}


static int	line_info(t_vars *vars, char *line, int count)
{
	char	**array;
	//int		fd; //check when we add textures

	array = ft_split(line, ' ');
	if (count >= 0 && count < 4)
	{
		if (line_first_word(array[0], count) == 1)
			return (1);
		/*
		check when we add textures
		fd = open(array[1], O_RDONLY);
		if (fd == -1)
			exit_error("ERROR - File Could Not Be Opened");
		*/
	}
	if ((count == 4 || count == 7) && line != NULL)
		return (1);
	if (count == 5 || count == 6) //F and C value
		if (fc_value(array, count) == 1)
			return (1);
	return (0);
}

void	add_to_map(t_vars *vars, int count)
{
	int		length;
	int		height;
	char	*line;
	int		line_num;
	int		map_line;

	height = count - 7;
	vars->height = height;
	vars->first_map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!vars->first_map)
	{
		free(vars)
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
		vars->first_map[map_line] = (char *)maloc(sizeof(char) * (length + 1));
		if (!vars->first_map[map_line])
		{
			free_map(vars->first_map, map_line);
			exit_error("ERROR - Malloc Error");
		}
		vars->first_map[map_line] = line; //strdup?
		line = get_next_line(fd);
		map_line++;
	}
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
		if (line_info(vars, line, count) == 1)
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
		count++;
	add_to_map(vars, count);
	return (0);
}

void	validate_file(t_vars *vars)
{
	int fd;

	if (hidden_file(vars->file, ".cub") == 1)
		exit_error("ERROR - Hidden File");
	if (ft_strncmp(vars->filele + ft_strlen(file) - 4, ".cub", 4) != 0)
		exit_error("ERROR - Wrong File Extension");
	fd = open(vars->file, O_RDONLY);
	if (fd == -1)
		exit_error("ERROR - File Could Not Be Opened");
	if (check_lines(vars) == 1)
		exit_error("ERROR - File Doesn't Contain Exact Info");
}
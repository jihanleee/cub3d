
static int	map_content(t_vars *vars)
{
	char	**map;
	char	*section;

	map = vars->first_map;
	while (*map)
	{
		section = *map;
		while (*sec)
		{
			if (*sec == 'N' || *sec == 'S' || *sec == 'E' || *sec == 'W')
				vars->players = vars->players + 1;
			else if (*sec != '1' && *sec != '0')
				return (1);
			sec++;
		}
		map++;
	}
	if (vars->players != 1)
		return (1);
	return (0);
}

void	parse_map(t_vars *vars)
{
	int	count;
	int	j;
	vars->map = (char **)malloc(sizeof(char *) * (vars->height + 1));
	if (!vars->first_map)
	{
		free(vars)
		exit_error("ERROR - Map Allocation Failed");
	}
	count = 0;
	while (*(vars->first_map))
	{
		j = 0;
		while (vars->first_map[count][j])
		{
			vars->map = (char *)malloc(sizeof(char *) * (vars->width + 1));
			if (vars->first_map[count][j] == ' ')
				vars->map[count][j] = 'X';
			else
				vars->map[count][j] = ft_strdup(vars->first_map[count][j]);
			j++;
		}
		count++;
	}
}


int	validate_map(t_var *vars)
{
	//check if all characters are valid
	//0, 1, N, S, E, or W
	if (map_content(vars) == 1)
		return (1);
	//change spaces to X
	parse_map(vars);
	//flood fill ==> check if player can reach X
}
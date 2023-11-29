
#include <stdio.h>
#include "cub3d.h"

static int	map_content(t_vars *vars)
{
	char	**map;
	char	*single;

	map = vars->first_map;
	while (*map)
	{
		single = *map;
		while (*single)
		{
			if (*single == 'N' || *single == 'S' || *single == 'E' || *single == 'W')
				vars->players = vars->players + 1;
			else if (*single != '1' && *single != '0' && *single != ' ' && *single != '\n')
				return (1);
			single++;
		}
		map++;
	}
	if (vars->players != 1)
		return (1);
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*new_string;

	len = 0;
	while (s[len])
		len++;
	new_string = (char *)malloc(sizeof (char) * (len + 1));
	if (new_string == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i++] = '\0';
	return (new_string);
}

char	*get_map_line(char *str, t_vars *vars)
{
	char	*new_string;
	int		i;

	new_string = (char *)malloc(sizeof(char) * (vars->width));
	if (!new_string)
	{
		free(new_string);
		//error message?
	}
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ' ')
			new_string[i] = 'X';
		else
			new_string[i] = str[i];
		i++;
	}
	while (i < vars->width - 1)
	{
		new_string[i] = 'X';
		i++;
	}
	new_string[i] = '\0';
	printf("new line: %s\n", new_string);
	return (new_string);
}

void	parse_map(t_vars *vars)
{
	int	count;
	char	*line;

	vars->map = (char **)malloc(sizeof(char *) * (vars->height + 1));
	if (!vars->map)
	{
		free(vars);
		exit_error("ERROR - Map Allocation Failed");
	}
	count = 0;
	while (vars->first_map[count])
	{
		line = get_map_line(vars->first_map[count], vars);
		//vars->map[count] = ft_strdup(line);
		vars->map[count] = line;
		//printf("%s\n", vars->map[count]);
		count++;
	}
}


int	validate_map(t_vars *vars)
{
	//check if all characters are valid
	//0, 1, N, S, E, or W
	if (map_content(vars) == 1)
		return (1);
	//change spaces to X
	parse_map(vars);
	//flood fill ==> check if player can reach X
	if (flood_fill(vars) ==1 )
		return (1);
	return (0);
}
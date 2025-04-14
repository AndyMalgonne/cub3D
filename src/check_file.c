/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:23:10 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/14 09:59:44 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_trim(char *str)
{
	int		start;
	int		end;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'))
		end--;
	return (ft_substr(str, start, end - start + 1));
}

void	texture_parsing(char *line, t_data *data)
{
	char	*trimmed_line;

	trimmed_line = ft_trim(line + 2);
	if (ft_strncmp(line, "NO", 2) == 0)
		data->no = trimmed_line;
	else if (ft_strncmp(line, "SO", 2) == 0)
		data->so = trimmed_line;
	else if (ft_strncmp(line, "WE", 2) == 0)
		data->we = trimmed_line;
	else if (ft_strncmp(line, "EA", 2) == 0)
		data->ea = trimmed_line;
	data->flag++;
}

void	color_parsing(char *line, t_data *data)
{
	char	*trimmed_line;

	trimmed_line = ft_trim(line + 1);
	if (ft_strncmp(line, "C", 1) == 0)
		data->ceiling = trimmed_line;
	else if (ft_strncmp(line, "F", 1) == 0)
		data->floor = trimmed_line;
	data->flag++;
}

char	**reallocate_map(char **map, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	while (map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

void	store_map(char *line, t_data *data)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (!data->map)
	{
		data->map = malloc(sizeof(char *) * 2);
		if (!data->map)
			return ;
		data->map[0] = ft_strdup(line);
		data->map[1] = NULL;
	}
	else
	{
		data->map = reallocate_map(data->map, line);
		if (!data->map)
			return ;
	}
}

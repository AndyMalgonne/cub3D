/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:23:10 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/07 10:39:15 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_parsing(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(line, "NO", 2) == 0)
		data->no = ft_strdup(line + i);
	else if (ft_strncmp(line, "SO", 2) == 0)
		data->so = ft_strdup(line + i);
	else if (ft_strncmp(line, "WE", 2) == 0)
		data->we = ft_strdup(line + i);
	else if (ft_strncmp(line, "EA", 2) == 0)
		data->ea = ft_strdup(line + i);
}

void	color_parsing(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(line, "C", 1) == 0)
		data->ceiling = ft_strdup(line + i);
	else if (ft_strncmp(line, "F", 1) == 0)
		data->floor = ft_strdup(line + i);
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

int	read_file(char *file, t_data *data)
{
	int		fd;
	char	*line;

	if (!is_cub(file))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0)
			texture_parsing(line, data);
		else if (ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0)
			color_parsing(line, data);
		else if (ft_strncmp(line, "1", 1) == 0 || line[0] == ' ')
			store_map(line, data);
		(free(line), line = get_next_line(fd));
	}
	close(fd);
	return (1);
}

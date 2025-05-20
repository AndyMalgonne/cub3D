/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:29:35 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 06:08:13 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_whitespace(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

static int	is_config_line(char *line)
{
	return (
		ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0
		|| ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0
	);
}

int	process_line(char *line, t_data *data, int *map_started, int fd)
{
	char	*trim;

	trim = skip_whitespace(line);
	if (is_line_empty(line) && (data->flag < 6 || !(*map_started)))
		return (free(line), 1);
	if (*map_started)
	{
		if (is_config_line(trim))
			return (free(line),
				printf("Error\nConfig lines error\n"), close(fd), 0);
	}
	if (ft_strncmp(trim, "NO", 2) == 0 || ft_strncmp(trim, "SO", 2) == 0
		|| ft_strncmp(trim, "EA", 2) == 0 || ft_strncmp(trim, "WE", 2) == 0)
	{
		if (!texture_parsing(trim, data))
			return (free(line), close(fd), 0);
	}
	else if (ft_strncmp(trim, "C", 1) == 0 || ft_strncmp(trim, "F", 1) == 0)
	{
		if (!color_parsing(trim, data))
			return (free(line), close(fd), 0);
	}
	else
		(store_map(line, data), *map_started = 1);
	return (free(line), 1);
}

int	read_file(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		map_started;

	map_started = 0;
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
		if (!process_line(line, data, &map_started, fd))
			return (0);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

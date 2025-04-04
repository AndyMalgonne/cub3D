/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:23:10 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/04 11:32:23 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub(char *file)
{
	int i;

	i = ft_strlen(file);
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i - 4] != '.')
		return(printf("Error\nInvalid file extension\n"), 0);
	return (1);
}

void texture_parsing(char *line, t_data *data)
{
    int i;

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

void color_parsing(char *line, t_data *data)
{
    int i;

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

void store_map(char *line, t_data *data)
{
    char *tmp;

    if (!data->map)
        data->map = ft_strdup(line);
    {
        tmp = data->map;
        data->map = ft_strjoin(data->map, line);
        free(tmp);
    }
}

int read_file(char *file, t_data *data)
{
    int fd;
    char *line;

    if (!is_cub(file))
        return (0);
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (0);
    }
    while ((line = get_next_line(fd)))
    {
        if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 ||
            ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0)
            texture_parsing(line, data);
        else if (ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0)
            color_parsing(line, data);
        else if (ft_strncmp(line, "1", 1) == 0 || line[0] == ' ')
            store_map(line, data);
        free(line);
    }
    close(fd);
    return (1);
}
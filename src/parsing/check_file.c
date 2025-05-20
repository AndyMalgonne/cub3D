/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:23:10 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 05:49:20 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_texture(char **texture, char *trimmed_line)
{
	if (*texture)
	{
		return (0);
	}
	*texture = trimmed_line;
	return (1);
}

int	handle_texture_id(char *line, char *trimmed_line, t_data *data)
{
	char	*ids[4];
	char	**paths[4];
	int		i;

	ids[0] = "NO";
	ids[1] = "SO";
	ids[2] = "WE";
	ids[3] = "EA";
	paths[0] = &data->textures->no_path;
	paths[1] = &data->textures->so_path;
	paths[2] = &data->textures->we_path;
	paths[3] = &data->textures->ea_path;
	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(line, ids[i], 2) == 0)
			return (assign_texture(paths[i], trimmed_line));
		i++;
	}
	return (0);
}

int	texture_parsing(char *line, t_data *data)
{
	char	*trimmed_line;
	int		ret;

	trimmed_line = ft_trim(line + 2);
	if (!trimmed_line)
		return (0);
	ret = handle_texture_id(line, trimmed_line, data);
	if (ret == 0)
	{
		free(trimmed_line);
		printf("Error\nInvalid texture identifier\n");
		return (0);
	}
	else if (ret == -1)
	{
		free(trimmed_line);
		return (0);
	}
	data->flag++;
	return (1);
}

int	color_parsing(char *line, t_data *data)
{
	char	*trimmed_line;

	trimmed_line = ft_trim(line + 1);
	if (ft_strncmp(line, "C", 1) == 0)
	{
		if (data->ceiling)
			return (printf("Error\nDuplicate color: C\n"),
				free(trimmed_line), 0);
		data->ceiling = trimmed_line;
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		if (data->floor)
			return (printf("Error\nDuplicate color: F\n"),
				free(trimmed_line), 0);
		data->floor = trimmed_line;
	}
	data->flag++;
	return (1);
}

void	store_map(char *line, t_data *data)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (!data->map)
	{
		data->map = ft_calloc(1, sizeof(char *) * 2);
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

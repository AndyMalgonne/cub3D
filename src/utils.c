/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:23:23 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/14 09:15:22 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_walls(t_data *data)
{
	if (!check_top_wall(data))
		return (0);
	if (!check_bottom_wall(data))
		return (0);
	if (!check_left_and_right_walls(data))
		return (0);
	return (1);
}

int	check_map(t_data *data)
{
	if (!check_map_closed(data))
		return (0);
	if (!check_walls(data))
		return (0);
	return (1);
}

int	check_color_texture_not_null(t_data *data)
{
	if (!data->no || !data->so || !data->ea || !data->we
		|| !data->ceiling || !data->floor)
	{
		printf("Error\nMissing texture or color information\n");
		return (0);
	}
	return (1);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

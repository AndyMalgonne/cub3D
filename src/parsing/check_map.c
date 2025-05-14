/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:57:25 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/14 22:38:47 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_top_wall(t_data *data)
{
	int	j;

	j = 0;
	while (data->map[0][j])
	{
		if (data->map[0][j] != '1' && (data->map[0][j] != ' '
			&& data->map[0][j] != '\t' && data->map[0][j] != '\n'))
			return (printf("Error\nMap is not closed at top\n"), 0);
		j++;
	}
	return (1);
}

int	check_bottom_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
		i++;
	i--;
	while (data->map[i][j])
	{
		if (data->map[i][j] != '1' && (data->map[i][j] != ' '
			&& data->map[i][j] != '\t' && data->map[i][j] != '\n'))
			return (printf("Error\nMap is not closed at bottom\n"), 0);
		j++;
	}
	return (1);
}

int	check_left_and_right_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && (data->map[i][j] == ' '
			|| data->map[i][j] == '\t'))
			j++;
		if (!data->map[i][j])
		{
			i++;
			continue ;
		}
		if (data->map[i][j] != '1')
			return (printf("Error\nMap is not closed at left\n"), 0);
		j = ft_strlen(data->map[i]) - 1;
		while (j >= 0 && (data->map[i][j] == ' ' || data->map[i][j] == '\t'))
			j--;
		if (j >= 0 && data->map[i][j] != '1')
			return (printf("Error\nMap is not closed at right\n"), 0);
		i++;
	}
	return (1);
}

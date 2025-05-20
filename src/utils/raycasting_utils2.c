/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 03:15:41 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 04:16:34 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_width(t_data *data, int row)
{
	if (!data->map || !data->map[row])
		return (0);
	return (ft_strlen(data->map[row]));
}

int	get_map_height(t_data *data)
{
	int	height;

	height = 0;
	while (data->map && data->map[height])
		height++;
	return (height);
}

int	is_valid_position(t_data *data, double x, double y)
{
	int	map_height;
	int	map_width;

	map_height = get_map_height(data);
	if (x < 0.1 || y < 0.1 || (int)y >= map_height)
		return (0);
	map_width = get_map_width(data, (int)y);
	if ((int)x >= map_width)
		return (0);
	if (data->map[(int)y][(int)x] == '1')
		return (0);
	return (1);
}

void	calculate_intermediate_position(t_move_data *move, int step)
{
	move->inter_x = move->curr_x + (move->new_x - move->curr_x) * (step / 10.0);
	move->inter_y = move->curr_y + (move->new_y - move->curr_y) * (step / 10.0);
}

void	invalid_pos(t_move_data *move, double last_x, double last_y, int i)
{
	if (i > 0)
	{
		move->new_x = last_x;
		move->new_y = last_y;
	}
	else
	{
		move->new_x = move->curr_x;
		move->new_y = move->curr_y;
	}
}

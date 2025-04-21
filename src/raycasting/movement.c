/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:42:41 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/21 15:38:15 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_data *data)
{
	double	move_speed;

	move_speed = 0.1;
	if (data->map[(int)(data->game->pos_y)][(int)(data->game->pos_x
			+ data->game->dir_x * move_speed)] != '1')
		data->game->pos_x += data->game->dir_x * move_speed;
	if (data->map[(int)(data->game->pos_y
			+ data->game->dir_y * move_speed)][(int)(data->game->pos_x)] != '1')
		data->game->pos_y += data->game->dir_y * move_speed;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->game->pos_x - data->game->dir_x * MOVE_SPEED;
	new_y = data->game->pos_y - data->game->dir_y * MOVE_SPEED;
	if (data->map[(int)new_y][(int)data->game->pos_x] != '1')
		data->game->pos_y = new_y;
	if (data->map[(int)data->game->pos_y][(int)new_x] != '1')
		data->game->pos_x = new_x;
}

void	strafe_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->game->pos_x - data->game->plane_x * MOVE_SPEED;
	new_y = data->game->pos_y - data->game->plane_y * MOVE_SPEED;
	if (data->map[(int)new_y][(int)data->game->pos_x] != '1')
		data->game->pos_y = new_y;
	if (data->map[(int)data->game->pos_y][(int)new_x] != '1')
		data->game->pos_x = new_x;
}

void	strafe_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->game->pos_x + data->game->plane_x * MOVE_SPEED;
	new_y = data->game->pos_y + data->game->plane_y * MOVE_SPEED;
	if (data->map[(int)new_y][(int)data->game->pos_x] != '1')
		data->game->pos_y = new_y;
	if (data->map[(int)data->game->pos_y][(int)new_x] != '1')
		data->game->pos_x = new_x;
}

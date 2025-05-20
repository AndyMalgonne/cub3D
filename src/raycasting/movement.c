/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:42:41 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 04:17:02 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_to_nearest_valid(t_data *data, t_move_data *move)
{
	double	last_x;
	double	last_y;
	int		i;

	last_x = move->curr_x;
	last_y = move->curr_y;
	i = 0;
	while (i <= 10)
	{
		calculate_intermediate_position(move, i);
		if (!is_valid_position(data, move->inter_x, move->inter_y))
		{
			invalid_pos(move, last_x, last_y, i);
			return ;
		}
		last_x = move->inter_x;
		last_y = move->inter_y;
		i++;
	}
	move->new_x = last_x;
	move->new_y = last_y;
}

void	move_forward(t_data *data)
{
	t_move_data	move;

	move.curr_x = data->game->pos_x;
	move.curr_y = data->game->pos_y;
	move.new_x = data->game->pos_x + data->game->dir_x * MOVE_SPEED;
	move.new_y = data->game->pos_y + data->game->dir_y * MOVE_SPEED;
	move_to_nearest_valid(data, &move);
	data->game->pos_x = move.new_x;
	data->game->pos_y = move.new_y;
}

void	move_backward(t_data *data)
{
	t_move_data	move;

	move.curr_x = data->game->pos_x;
	move.curr_y = data->game->pos_y;
	move.new_x = data->game->pos_x - data->game->dir_x * MOVE_SPEED;
	move.new_y = data->game->pos_y - data->game->dir_y * MOVE_SPEED;
	move_to_nearest_valid(data, &move);
	data->game->pos_x = move.new_x;
	data->game->pos_y = move.new_y;
}

void	strafe_left(t_data *data)
{
	t_move_data	move;

	move.curr_x = data->game->pos_x;
	move.curr_y = data->game->pos_y;
	move.new_x = data->game->pos_x - data->game->plane_x * MOVE_SPEED;
	move.new_y = data->game->pos_y - data->game->plane_y * MOVE_SPEED;
	move_to_nearest_valid(data, &move);
	data->game->pos_x = move.new_x;
	data->game->pos_y = move.new_y;
}

void	strafe_right(t_data *data)
{
	t_move_data	move;

	move.curr_x = data->game->pos_x;
	move.curr_y = data->game->pos_y;
	move.new_x = data->game->pos_x + data->game->plane_x * MOVE_SPEED;
	move.new_y = data->game->pos_y + data->game->plane_y * MOVE_SPEED;
	move_to_nearest_valid(data, &move);
	data->game->pos_x = move.new_x;
	data->game->pos_y = move.new_y;
}

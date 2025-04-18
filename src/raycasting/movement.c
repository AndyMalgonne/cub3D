/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:42:41 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/18 14:55:56 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_data *data)
{
	double newX = data->game->posX + data->game->dirX * MOVE_SPEED;
	double newY = data->game->posY + data->game->dirY * MOVE_SPEED;

	if (data->map[(int)newY][(int)data->game->posX] != '1')
		data->game->posY = newY;
	if (data->map[(int)data->game->posY][(int)newX] != '1')
		data->game->posX = newX;
}

void	move_backward(t_data *data)
{
	double newX = data->game->posX - data->game->dirX * MOVE_SPEED;
	double newY = data->game->posY - data->game->dirY * MOVE_SPEED;

	if (data->map[(int)newY][(int)data->game->posX] != '1')
		data->game->posY = newY;
	if (data->map[(int)data->game->posY][(int)newX] != '1')
		data->game->posX = newX;
}

void	strafe_left(t_data *data)
{
	double newX = data->game->posX - data->game->planeX * MOVE_SPEED;
	double newY = data->game->posY - data->game->planeY * MOVE_SPEED;

	if (data->map[(int)newY][(int)data->game->posX] != '1')
		data->game->posY = newY;
	if (data->map[(int)data->game->posY][(int)newX] != '1')
		data->game->posX = newX;
}

void	strafe_right(t_data *data)
{
	double newX = data->game->posX + data->game->planeX * MOVE_SPEED;
	double newY = data->game->posY + data->game->planeY * MOVE_SPEED;

	if (data->map[(int)newY][(int)data->game->posX] != '1')
		data->game->posY = newY;
	if (data->map[(int)data->game->posY][(int)newX] != '1')
		data->game->posX = newX;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:44:17 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/18 14:44:35 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_data *data)
{
	double oldDirX = data->game->dirX;
	data->game->dirX = data->game->dirX * cos(-ROT_SPEED) - data->game->dirY * sin(-ROT_SPEED);
	data->game->dirY = oldDirX * sin(-ROT_SPEED) + data->game->dirY * cos(-ROT_SPEED);

	double oldPlaneX = data->game->planeX;
	data->game->planeX = data->game->planeX * cos(-ROT_SPEED) - data->game->planeY * sin(-ROT_SPEED);
	data->game->planeY = oldPlaneX * sin(-ROT_SPEED) + data->game->planeY * cos(-ROT_SPEED);
}

void	rotate_right(t_data *data)
{
	double oldDirX = data->game->dirX;
	data->game->dirX = data->game->dirX * cos(ROT_SPEED) - data->game->dirY * sin(ROT_SPEED);
	data->game->dirY = oldDirX * sin(ROT_SPEED) + data->game->dirY * cos(ROT_SPEED);

	double oldPlaneX = data->game->planeX;
	data->game->planeX = data->game->planeX * cos(ROT_SPEED) - data->game->planeY * sin(ROT_SPEED);
	data->game->planeY = oldPlaneX * sin(ROT_SPEED) + data->game->planeY * cos(ROT_SPEED);
}

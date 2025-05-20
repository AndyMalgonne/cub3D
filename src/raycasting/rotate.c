/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:44:17 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 04:41:24 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->game->dir_x;
	data->game->dir_x = data->game->dir_x * cos(ROT_SPEED)
		- data->game->dir_y * sin(ROT_SPEED);
	data->game->dir_y = old_dir_x * sin(ROT_SPEED)
		+ data->game->dir_y * cos(ROT_SPEED);
	old_plane_x = data->game->plane_x;
	data->game->plane_x = data->game->plane_x * cos(ROT_SPEED)
		- data->game->plane_y * sin(ROT_SPEED);
	data->game->plane_y = old_plane_x * sin(ROT_SPEED)
		+ data->game->plane_y * cos(ROT_SPEED);
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->game->dir_x;
	data->game->dir_x = data->game->dir_x * cos(-ROT_SPEED)
		- data->game->dir_y * sin(-ROT_SPEED);
	data->game->dir_y = old_dir_x * sin(-ROT_SPEED)
		+ data->game->dir_y * cos(-ROT_SPEED);
	old_plane_x = data->game->plane_x;
	data->game->plane_x = data->game->plane_x * cos(-ROT_SPEED)
		- data->game->plane_y * sin(-ROT_SPEED);
	data->game->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ data->game->plane_y * cos(-ROT_SPEED);
}

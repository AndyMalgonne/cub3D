/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:25 by amalgonn          #+#    #+#             */
/*   Updated: 2025/05/20 04:41:37 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_plane(t_game *game)
{
	game->plane_x = -game->dir_y * 0.66;
	game->plane_y = game->dir_x * 0.66;
}

int	set_direction(t_game *game, char pos)
{
	if (pos == 'N')
	{
		game->dir_x = 0;
		game->dir_y = -1;
	}
	else if (pos == 'S')
	{
		game->dir_x = 0;
		game->dir_y = 1;
	}
	else if (pos == 'E')
	{
		game->dir_x = 1;
		game->dir_y = 0;
	}
	else if (pos == 'W')
	{
		game->dir_x = -1;
		game->dir_y = 0;
	}
	else
		return (printf("Error\nInvalid position\n"), 0);
	set_plane(game);
	return (1);
}

int	get_player_position_and_direction(t_data *data, t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			c = data->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->pos_x = j + 0.5;
				game->pos_y = i + 0.5;
				data->map[i][j] = '0';
				return (set_direction(game, c));
			}
			j++;
		}
		i++;
	}
	return (printf("Error\nNo player position found\n"), 0);
}

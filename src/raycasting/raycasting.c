/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:36:25 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/18 15:26:51 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_direction(t_game *game, char pos)
{
	if (pos == 'N')
	{
		game->dirX = 0;
		game->dirY = -1;
		game->planeX = -0.66;
		game->planeY = 0;
	}
	else if (pos == 'S')
	{
		game->dirX = 0;
		game->dirY = 1;
		game->planeX = 0.66;
		game->planeY = 0;
	}
	else if (pos == 'E')
	{
		game->dirX = 1;
		game->dirY = 0;
		game->planeX = 0;
		game->planeY = 0.66;
	}
	else if (pos == 'W')
	{
		game->dirX = -1;
		game->dirY = 0;
		game->planeX = 0;
		game->planeY = -0.66;
	}
	else
		return(printf("Error\nInvalid position\n"), 0);
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
				game->posX = j + 0.5;
				game->posY = i + 0.5;
				data->map[i][j] = '0';
				return (set_direction(game, c));
			}
			j++;
		}
		i++;
	}
	return (printf("Error\nNo player position found\n"), 0);
}

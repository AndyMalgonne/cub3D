/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:57:25 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/04 14:58:49 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_valid_char(t_data *data)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
                data->map[i][j] == 'E' || data->map[i][j] == 'W')
                player_count++;
            else if (data->map[i][j] != '1' && data->map[i][j] != '0' &&
                     data->map[i][j] != ' ' && data->map[i][j] != 'N' &&
					data->map[i][j] != 'S' && data->map[i][j] != 'E' &&
					data->map[i][j] != 'W')
                return (printf("Error\nInvalid characters in map\n"), 0);
            j++;
        }
        i++;
    }
    if (player_count != 1)
        return (printf("Error\nToo many or no players in map\n"), 0);
    return (1);
}

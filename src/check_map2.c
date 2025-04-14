/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:33:59 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/14 10:09:05 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_surroundings(t_data *data, int i, int j)
{
	if (i == 0 || j == 0 || !data->map[i + 1] || !data->map[i][j + 1])
		return (printf("Error\nMap open at edge near (%d, %d)\n",
				(i + 1), (j + 1)), 0);
	if (i > 0 && (j >= (int)ft_strlen(data->map[i - 1])
			|| (data->map[i - 1][j] == ' ' || data->map[i - 1][j] == '\t')))
		return (printf("Error\nMap open near space at (%d, %d)\n",
				(i + 1), (j + 1)), 0);
	if (data->map[i + 1] && (j >= (int)ft_strlen(data->map[i + 1])
			|| (data->map[i + 1][j] == ' ') || data->map[i + 1][j] == '\t'))
		return (printf("Error\nMap open near space at (%d, %d)\n",
				(i + 1), (j + 1)), 0);
	if (j > 0 && (data->map[i][j - 1] == ' ' || data->map[i][j - 1] == '\t'))
		return (printf("Error\nMap open near space at (%d, %d)\n",
				(i + 1), (j + 1)), 0);
	if (j + 1 >= (int)ft_strlen(data->map[i]) || (data->map[i][j + 1] == ' '
		|| data->map[i][j + 1] == '\t'))
		return (printf("Error\nMap open near space at (%d, %d)\n",
				(i + 1), (j + 1)), 0);
	return (1);
}

int	validate_player_count(int player_count)
{
	if (player_count != 1)
	{
		printf("Error\nToo many or no players in map\n");
		return (0);
	}
	return (1);
}

int	check_invalid_char(t_data *data, int i, int j)
{
	char	c;

	c = data->map[i][j];
	if (c == '\t')
		c = ' ';
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != '0' && c != '1' && c != ' ')
	{
		printf("Error\nInvalid character '%c' at (%d, %d)\n", c, i, j);
		return (0);
	}
	return (1);
}

int	check_row(t_data *data, int i, int *player_count)
{
	int	j;

	j = 0;
	while (data->map[i][j])
	{
		if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
			data->map[i][j] == 'E' || data->map[i][j] == 'W')
		{
			(*player_count)++;
			if (!check_surroundings(data, i, j))
				return (0);
		}
		else if (data->map[i][j] == '0')
		{
			if (!check_surroundings(data, i, j))
				return (0);
		}
		else if (!check_invalid_char(data, i, j))
			return (0);
		j++;
	}
	return (1);
}

int	check_map_closed(t_data *data)
{
	int	i;
	int	player_count;
	if (!data->map || !data->map[0])
		return (printf("Error\nMap is empty\n"), 0);
	i = 0;
	player_count = 0;
	while (data->map[i])
	{
		if (!check_row(data, i, &player_count))
			return (0);
		i++;
	}
	return (validate_player_count(player_count));
}

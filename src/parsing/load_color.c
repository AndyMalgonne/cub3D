/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:59:59 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/29 09:40:26 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_and_trim_rgb(char **rgb)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < 3)
	{
		trimmed = ft_trim(rgb[i]);
		free(rgb[i]);
		rgb[i] = trimmed;
		if (!is_valid_number(rgb[i]))
			return (ft_fsplit(rgb),
				printf("Error\nColor values must be digits only\n"), 0);
		i++;
	}
	return (1);
}

int parse_color(char *line)
{
    char **rgb;
    int r, g, b, color;
    char *trimmed_line;

    trimmed_line = ft_trim(line);
    if (!trimmed_line)
        return (-1);
    rgb = ft_split(trimmed_line, ',');
    free(trimmed_line);
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
        return (ft_fsplit(rgb), printf("Error\nInvalid color format\n"), -1);
    if (!validate_and_trim_rgb(rgb))
        return (-1);
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (ft_fsplit(rgb), printf("Error\nColor values must be between 0 and 255\n"), -1);
    color = (r << 16) | (g << 8) | b;
    ft_fsplit(rgb);
    return (color);
}

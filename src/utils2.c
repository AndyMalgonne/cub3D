/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalgonn <amalgonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:15:06 by amalgonn          #+#    #+#             */
/*   Updated: 2025/04/30 07:59:44 by amalgonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cub(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (file[i - 1] != 'b' || file[i - 2] != 'u'
		|| file[i - 3] != 'c' || file[i - 4] != '.')
		return (printf("Error\nInvalid file extension\n"), 0);
	return (1);
}

char	*ft_trim(char *str)
{
	int		start;
	int		end;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'
			|| str[start] == '\n'))
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'
			|| str[end] == '\n'))
		end--;
	return (ft_substr(str, start, end - start + 1));
}

void	ft_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**reallocate_map(char **map, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	while (map[i])
		i++;
	new_map = ft_calloc(1, sizeof(char *) * (i + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
	{
		while (i > 0)
			free(new_map[--i]);
		free(new_map);
		return (NULL);
	}
	new_map[i + 1] = NULL;
	return (free(map), new_map);
}

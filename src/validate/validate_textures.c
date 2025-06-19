/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:23:05 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/14 17:45:50 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	is_duplicate_texture(char *texture_type)
{
	if (texture_type[0] != '\0')
	{
		ft_putstr_fd("Error\nDuplicate texture path\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	process_texture(char **map, char *texture_type, char a, char b)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] == ' ' && map[i][j] != '\0')
			j++;
		if (map[i][j] == a && map[i][j + 1] == b && map[i][j + 2] == ' ')
		{
			j += 2;
			if (is_duplicate_texture(texture_type) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			texture_type = extract(map, i, j, texture_type);
			if (texture_type == NULL)
				return (ft_putstr_fd("Error\nInvalid texture.\n", 2), 1);
		}
		i++;
	}
	if (texture_type[0] == '\0')
		return (ft_putstr_fd("Error\nAt least 1 texture not found.\n", 2), 1);
	if (validate_extension(texture_type, 'p', 'n', 'g') == 1)
		return (ft_putstr_fd("Error\nWrong texture file. Usage: *.png\n", 2), 1);
	return (EXIT_SUCCESS);
}

int	validate_texture(char **map, t_game *game)
{
	int	exit;

	exit = 0;
	exit += process_texture(map, game->data->no, 'N', 'O');
	exit += process_texture(map, game->data->so, 'S', 'O');
	exit += process_texture(map, game->data->we, 'W', 'E');
	exit += process_texture(map, game->data->ea, 'E', 'A');
	if (exit != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

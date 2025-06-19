/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:42:55 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/25 17:27:44 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static uint32_t	extract_rgb(char **map, int i, int j, uint32_t rbg_type)
{
	char	*rgb;
	char	**rgb_split;
	int		k;

	k = 0;
	rgb = ft_calloc(256, sizeof(char));
	if (rgb == NULL)
		return (ft_putstr_fd("Error\n calloc failed for rgb\n", 2), '\0');
	extract(map, i, j, rgb);
	if (check_rgb(rgb) == 1)
		return (free(rgb), '\0');
	rgb_split = ft_split(rgb, ',');
	free(rgb);
	if (!rgb_split)
		return ('\0');
	if (validate_rgb_split(rgb_split) == 1)
		return (free_char_array(rgb_split), '\0');
	rbg_type = create_color(ft_atoi(rgb_split[0]), \
			ft_atoi(rgb_split[1]), ft_atoi(rgb_split[2]), 255);
	free_char_array(rgb_split);
	return (rbg_type);
}

static int	process_rgb(char **map, uint32_t *rbg_type, char a)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] == ' ' && map[i][j] != '\0')
			j++;
		if (map[i][j] == a && map[i][j + 1] == ' ')
		{
			j++;
			if (is_duplicate_rgb(*rbg_type) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			*rbg_type = extract_rgb(map, i, j, *rbg_type);
		}
		i++;
	}
	if (*rbg_type == '\0')
		return (ft_putstr_fd("Error\nAt least 1 rgb not found.\n", 2), 1);
	return (EXIT_SUCCESS);
}

int	validate_rgb(char **map, t_game *game)
{
	if (process_rgb(map, &game->data->floor, 'F') == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (process_rgb(map, &game->data->ceiling, 'C') == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

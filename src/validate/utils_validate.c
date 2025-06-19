/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:53:36 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/26 16:29:34 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	*extract(char **map, int i, int j, char *extract)
{
	int	k;

	k = 0;
	while (map[i][j] == ' ')
		j++;
	while (map[i][j] != ' ' && map[i][j] != '\0')
	{
		extract[k] = map[i][j];
		j++;
		k++;
	}
	while (map[i][j] != '\0')
	{
		if (map[i][j] != ' ')
		{
			extract[i] = '\0';
			extract = NULL;
			return (NULL);
		}
		j++;
	}
	extract[k] = '\0';
	return (extract);
}

int	is_duplicate_rgb(uint32_t rbg_type)
{
	if (rbg_type != '\0')
	{
		ft_putstr_fd("Error\nDuplicate rgb path\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

uint32_t	create_color(int r, int g, int b, int a)
{
	return (a << 24 | b << 16 | g << 8 | r);
}

int	check_rgb(char *rgb)
{
	int	i;

	i = 0;
	if (rgb == NULL)
		return (EXIT_FAILURE);
	while (rgb[i])
	{
		if ((rgb[i] == ',' && rgb[i + 1] == ',')
			|| (rgb[i] == ',' && rgb[i + 1] == '\0')
			|| (!ft_isdigit(rgb[i]) && rgb[i] != ' ' && rgb[i] != ','))
		{
			ft_putstr_fd("Error\nInvalid rgb color.\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	validate_rgb_split(char **rgb_split)
{
	int	count;
	int	color;

	count = 0;
	while (rgb_split[count] != NULL)
		count++;
	if (count != 3)
	{
		ft_putstr_fd("Error\nInvalid rgb color.\n", 2);
		return (EXIT_FAILURE);
	}
	count = 0;
	while (rgb_split[count] != NULL)
	{
		color = ft_atoi(rgb_split[count]);
		if (color < 0 || color > 255)
		{
			ft_putstr_fd("Error\nInvalid rgb color.\n", 2);
			return (EXIT_FAILURE);
		}
		count++;
	}
	return (EXIT_SUCCESS);
}

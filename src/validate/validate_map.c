/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:22:54 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/19 12:49:27 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	check_char(t_data *data, int i, int j, int *count)
{
	const char	c = data->map[i][j];

	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ' && c != '\t')
	{
		ft_putstr_fd("Error\nWrong map component.\n", 2);
		return (EXIT_FAILURE);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->dir_player = c;
		data->player_pos.x = j;
		data->player_pos.y = i;
		(*count)++;
	}
	return (EXIT_SUCCESS);
}

int	valid_chars(t_data *data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (check_char(data, i, j, &count) == 1)
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		ft_putstr_fd("Error\nLess or more than 1 starting position.\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

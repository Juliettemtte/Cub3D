/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:53:34 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/26 16:32:42 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	compute_map_size(t_data *data, char **cub_content, int start, int i)
{
	int	k;
	int	j;
	int	max_width;

	k = start;
	max_width = 0;
	data->map_size.y = i - start;
	while (k < i)
	{
		j = ft_strlen(cub_content[k]);
		if (j > max_width)
			max_width = j;
		k++;
	}
	data->map_size.x = max_width;
}

int	is_map(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if ((s[i] == 'N' && s[i + 1] == 'O') || (s[i] == 'S' && s[i + 1] == 'O')
		|| (s[i] == 'E' && s[i + 1] == 'A') || (s[i] == 'W' && s[i + 1] == 'E')
		|| s[i] == 'F' || s[i] == 'C')
		return (3);
	if (!(s[i] == '0' || s[i] == '1' || s[i] == 'N' || s[i] == 'S'
			|| s[i] == 'E' || s[i] == 'W'))
		return (3);
	while (s[i])
	{
		if (s[i] == '0' || s[i] == '1' || s[i] == 'N' || s[i] == 'S'
			|| s[i] == 'E' || s[i] == 'W')
			return (EXIT_SUCCESS);
		i++;
	}
	if (s[i] == '\0')
		return (2);
	return (EXIT_FAILURE);
}

static int	fill_map(t_data *data, char **cub_content, int map_start, int i)
{
	int	j;
	int	k;
	int	len;

	j = 0;
	while (map_start < i)
	{
		data->map[j] = ft_calloc(data->map_size.x + 1, sizeof(char));
		if (!data->map[j])
			return (ft_putstr_fd("Error\nMalloc failed for map\n", 2), 1);
		len = ft_strlen(cub_content[map_start]);
		ft_memcpy(data->map[j], cub_content[map_start], len);
		k = len;
		while (k < data->map_size.x)
		{
			data->map[j][k] = ' ';
			k++;
		}
		data->map[j][data->map_size.x] = '\0';
		map_start++;
		j++;
	}
	data->map[j] = NULL;
	return (0);
}

int	copy_map(t_data *data, char **cub_content, int map_start, int i)
{
	if (map_start == -1)
		return (ft_putstr_fd("Error\nNo map found.\n", 2), EXIT_FAILURE);
	compute_map_size(data, cub_content, map_start, i);
	data->map = ft_calloc((data->map_size.y + 1), sizeof(char *));
	if (!data->map)
		return (ft_putstr_fd("Error\nMalloc failed for map\n", 2), EXIT_FAILURE);
	if (fill_map(data, cub_content, map_start, i) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	empty_lines(char *line)
{
	int	j;

	j = 0;
	while (line[j] != '\0')
	{
		if (line[j] != ' ' && line[j] != '\t')
			return (0);
		j++;
	}
	return (1);
}

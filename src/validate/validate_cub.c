/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:11:53 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/26 16:32:41 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	validate_extension(char *name, char a, char b, char c)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 5)
		return (EXIT_FAILURE);
	if (len > 5 && (name[len - 5] == ' ' || name[len - 5] == '/'))
		return (EXIT_FAILURE);
	if (name[len - 4] == '.' && name[len - 3] == a && name[len - 2] == b
		&& name[len - 1] == c)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

void	make_map_rectangular(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_size.y)
	{
		j = 0;
		while (j < data->map_size.x)
		{
			if (j >= (int)ft_strlen(data->map[i]))
				data->map[i][j] = '1';
			else if (data->map[i][j] == ' ' || data->map[i][j] == '\t')
				data->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

static int	read_copy_map(char **cub_content, t_data *data)
{
	int	i;
	int	map_start;

	i = 0;
	map_start = -1;
	while (cub_content[i] != NULL)
	{
		if (is_map(cub_content[i]) == 0)
		{
			map_start = i;
			while (cub_content[i] != NULL && is_map(cub_content[i]) == 0)
				i++;
			while (cub_content[i] != NULL)
			{
				if (is_map(cub_content[i]) != 2 && !empty_lines(cub_content[i]))
					return (printf("Error\nMap is not at the end.\n"), 1);
				i++;
			}
			break ;
		}
		i++;
	}
	if (copy_map(data, cub_content, map_start, i) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	validate_cub(char *map_name, t_game *game)
{
	char	**cub_content;
	int		exit;

	exit = 0;
	if (validate_extension(map_name, 'c', 'u', 'b') == 1)
		return (ft_putstr_fd("Error\nWrong map file. Usage: *.cub\n", 2), 1);
	cub_content = read_map(map_name);
	if (cub_content == NULL)
		return (EXIT_FAILURE);
	exit += validate_texture(cub_content, game);
	exit += validate_rgb(cub_content, game);
	if (exit != 0)
		return (free_char_array(cub_content), EXIT_FAILURE);
	exit += read_copy_map(cub_content, game->data);
	free_char_array(cub_content);
	if (exit != 0)
		return (EXIT_FAILURE);
	exit += valid_chars(game->data);
	exit += is_accessible(game->data);
	if (exit != 0)
		return (EXIT_FAILURE);
	make_map_rectangular(game->data);
	return (EXIT_SUCCESS);
}

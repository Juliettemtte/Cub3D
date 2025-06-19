/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:46:22 by jmouette          #+#    #+#             */
/*   Updated: 2025/02/19 12:54:14 by jmouette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	ft_count_lines(char *file_content)
{
	int	count;
	int	i;

	if (!file_content)
		return (0);
	count = 0;
	i = 0;
	while (file_content[i])
	{
		if (file_content[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && file_content[i - 1] != '\n')
		count++;
	return (count);
}

static char	**split_keep_empty_lines(char *file_content)
{
	char	**map;
	int		i;
	int		len;

	map = ft_calloc(ft_count_lines(file_content) + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (*file_content)
	{
		len = 0;
		while (file_content[len] && file_content[len] != '\n')
			len++;
		map[i] = ft_substr(file_content, 0, len);
		if (!map[i])
			return (free_char_array(map), NULL);
		if (file_content[len] == '\n')
			file_content += len + 1;
		else
			file_content += len;
		i++;
	}
	map[i] = NULL;
	return (map);
}

static char	*read_file_content(int fd)
{
	char	*file_content;
	char	*line;
	char	*tmp_content;

	file_content = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp_content = file_content;
		file_content = ft_strjoin(tmp_content, line);
		free(line);
		free(tmp_content);
		line = get_next_line(fd);
	}
	return (file_content);
}

char	**read_map(char *path)
{
	int		fd;
	char	*file_content;
	char	**map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nNo such file or directory\n", 2);
		return (NULL);
	}
	file_content = read_file_content(fd);
	close(fd);
	if (ft_strlen(file_content) == 0)
	{
		free(file_content);
		ft_putstr_fd("Error\nFile is empty.\n", 2);
		return (NULL);
	}
	map = split_keep_empty_lines(file_content);
	free(file_content);
	return (map);
}

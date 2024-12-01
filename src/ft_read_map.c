/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:59:55 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/01 17:51:31 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*clean_line(char *line)
{
	char	*cleaned;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	cleaned = ft_strdup(line);
	free(line);
	return (cleaned);
}

static int	count_lines(const char *filename)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (count);
}

t_map	*read_map(const char *filename)
{
	t_map	*map;
	int		fd;
	int		i;

	map = malloc(sizeof(t_map));
	map->height = count_lines(filename);
	if (map->height < 3)
		return (free(map), NULL);
	map->grid = malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return (free(map), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = clean_line(get_next_line(fd));
		if (!map->grid[i])
			free_map(map);
		i++;
	}
	close(fd);
	map->width = ft_strlen(map->grid[0]);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:59:55 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/04 16:57:09 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*clean_line(char *line)
{
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
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

static int	populate_map_grid(t_map *map, int fd)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		map->grid[i] = clean_line(get_next_line(fd));
		if (!map->grid[i])
			return (0);
		i++;
	}
	return (1);
}

t_map	*read_map(const char *filename)
{
	t_map	*map;
	int		fd;

	map = malloc(sizeof(t_map));
	map->height = count_lines(filename);
	if (map->height < 3)
		return (free(map), NULL);
	map->grid = malloc(sizeof(char **) * map->height);
	if (!map->grid)
		return (free(map), NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !populate_map_grid(map, fd))
		return (free_map(map), NULL);
	close(fd);
	map->width = ft_strlen(map->grid[0]);
	return (map);
}

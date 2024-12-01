/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 04:15:04 by lserrao-          #+#    #+#             */
/*   Updated: 2024/11/30 17:56:36 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill_path(char **grid, int y, int x)
{
	if (grid[y][x] != 'P')
	{
		if (grid[y][x] == '0')
			grid[y][x] = 'o';
		else if (grid[y][x] == 'C')
			grid[y][x] = 'c';
		else if (grid[y][x] == 'E')
			grid[y][x] = 'e';
		else
			return ;
	}
	fill_path(grid, y + 1, x);
	fill_path(grid, y - 1, x);
	fill_path(grid, y, x + 1);
	fill_path(grid, y, x - 1);
}

int	validate_path(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	fill_path(game->map->grid, game->player_y, game->player_x);
	while (i < game->map->height)
	{
		j = 0;
		while (game->map->grid[i][j])
		{
			if ((game->map->grid[i][j] == 'E')
				|| (game->map->grid[i][j] == 'C'))
				return (0);
			if (game->map->grid[i][j] == 'o')
					game->map->grid[i][j] = '0';
			else if (game->map->grid[i][j] == 'c')
				game->map->grid[i][j] = 'C';
			else if (game->map->grid[i][j] == 'e')
				game->map->grid[i][j] = 'E';
			j++;
		}
		i++;
	}
	return (1);
}

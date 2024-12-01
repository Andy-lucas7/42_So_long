/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 07:53:12 by lserrao-          #+#    #+#             */
/*   Updated: 2024/11/30 20:00:17 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_grid(char **grid, int height)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (map->grid)
	{
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	cleanup_game(t_game *game)
{
	cleanup_textures(game);
	free_map(game->map);
	exit (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd ("Error:\nUsage: ./so_long <map.ber>\n", 1);
		return (0);
	}
	if (!init_game(&game, argv[1]))
		return (cleanup_game(&game), 0);
	render_map(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_set_icon(game.mlx, game.textures[5]);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}

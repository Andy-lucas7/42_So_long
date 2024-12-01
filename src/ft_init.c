/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:34:46 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/01 17:52:04 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	game->textures[0] = mlx_load_png("./src/img/zero64.png");
	game->textures[1] = mlx_load_png("./src/img/one64.png");
	game->textures[2] = mlx_load_png("./src/img/idle_down64.png");
	game->textures[3] = mlx_load_png("./src/img/portal.png");
	game->textures[4] = mlx_load_png("./src/img/collectible64.png");
	game->textures[5] = mlx_load_png("./src/img/icon.png");
	while (i < 6)
	{
		game->tiles[i] = mlx_texture_to_image(game->mlx, game->textures[i]);
		if (!game->tiles[i])
		{
			cleanup_textures(game);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_game(t_game *game, char *map_file)
{
	ft_memset(game, 0, sizeof(t_game));
	game->moves = 0;
	game->map = read_map(map_file);
	if (!read_map(map_file))
		return (ft_putstr_fd("Error:\nInvalid map or invalid path\n", 1),
			cleanup_game(game), 0);
	ft_find_char('P', game);
	if (!validate_map(game->map, game))
	{
		ft_putstr_fd("Error:\nInvalid map or invalid path\n", 1);
		return (cleanup_game(game), 0);
	}
	game->mlx = mlx_init(game->map->width * TILE_SIZE, \
	game->map->height * TILE_SIZE, "so_long", true);
	if (!game->mlx)
		return (free_map(game->map), 0);
	if (!load_textures(game))
	{
		ft_putstr_fd("Error:\nFailed to load textures\n", 1);
		free_map(game->map);
		mlx_terminate(game->mlx);
		return (0);
	}
	return (1);
}

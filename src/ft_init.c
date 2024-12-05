/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 02:34:46 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/04 23:14:05 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	game->textures[0] = mlx_load_png("./textures/zero64.png");
	game->textures[1] = mlx_load_png("./textures/one64.png");
	game->textures[2] = mlx_load_png("./textures/idle_down64.png");
	game->textures[3] = mlx_load_png("./textures/portal.png");
	game->textures[4] = mlx_load_png("./textures/collectible64.png");
	game->textures[5] = mlx_load_png("./textures/icon.png");
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

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE, "so_long", true);
	if (!game->mlx)
	{
		return (0);
	}
	if (!load_textures(game))
	{
		ft_putstr_fd("Error:\nFailed to load textures\n", 1);
		cleanup_game(game);
		return (0);
	}
	return (1);
}

int	init_game(t_game *game, char *map_file)
{
	ft_memset(game, 0, sizeof(t_game));
	game->moves = 0;
	game->map = read_map(map_file);
	if (!game->map)
	{
		ft_putstr_fd("Error:\nInvalid map!\n", 2);
		return (0);
	}
	ft_find_char('P', game);
	if (!validate_map(game->map, game))
		return (0);
	return (init_mlx(game));
}

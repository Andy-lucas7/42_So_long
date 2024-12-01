/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 00:36:23 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/01 01:10:58 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map->width)
		return (0);
	if (new_y < 0 || new_y >= game->map->height)
		return (0);
	if (game->map->grid[new_y][new_x] == '1')
		return (0);
	return (1);
}

static void	validate_win(t_game *game)
{
	if (game->map->collectibles > 0)
	{
		game->map->grid[game->player_y][game->player_x] = 'E';
	}
	else
	{
		ft_putstr_fd("\nCongratulations! You won in ", 1);
		ft_putnbr_fd (game->moves, 1);
		ft_putstr_fd (" moves!\n", 1);
		cleanup_game(game);
	}
}

void	process_move(t_game *game, int new_x, int new_y)
{
	if (game->map->grid[new_y][new_x] == 'C')
	{
		game->map->collectibles--;
		game->map->grid[new_y][new_x] = '0';
		render_tile(game, new_x, new_y);
	}
	if (game->map->grid[new_y][new_x] == 'E')
	{
		validate_win (game);
		if (game->map->collectibles > 0)
			return ;
	}
	game->map->grid[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
	game->map->grid[new_y][new_x] = 'P';
	mlx_delete_image(game->mlx, game->tiles[2]);
	game->tiles[2] = mlx_texture_to_image(game->mlx, game->textures[2]);
	mlx_image_to_window(game->mlx, game->tiles[2], \
	new_x * TILE_SIZE, new_y * TILE_SIZE);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		new_x;
	int		new_y;

	game = (t_game *)param;
	new_x = game->player_x;
	new_y = game->player_y;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		cleanup_game(game);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		new_y--;
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		new_y++;
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		new_x--;
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		new_x++;
	else
		return ;
	if (validate_move(game, new_x, new_y))
		process_move(game, new_x, new_y);
}

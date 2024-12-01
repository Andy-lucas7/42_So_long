/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserrao- <lserrao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:53:43 by lserrao-          #+#    #+#             */
/*   Updated: 2024/12/01 17:46:57 by lserrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "../include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# define TILE_SIZE 64

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
}	t_map;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*tiles[6];
	mlx_texture_t	*textures[6];
	int				player_x;
	int				player_y;
	int				moves;
	t_map			*map;
}	t_game;

void		ft_find_char(char c, t_game *game);
int			validate_map(t_map *map, t_game *game);
void		cleanup_textures(t_game *game);
void		render_tile(t_game *game, int x, int y);
t_map		*read_map(const char *filename);
void		free_map(t_map *map);
void		free_grid(char **grid, int height);
int			load_textures(t_game *game);
void		render_map(t_game *game);
void		key_hook(mlx_key_data_t keydata, void *param);
int			init_game(t_game *game, char *map_file);
void		cleanup_game(t_game *game);
int			validate_path(t_game *game);

#endif
//*******************pngs's array*********************//
//0=floor, 1=wall, 2=player, 3=exit, 4=collect, 5=icon//
//***************************************************//
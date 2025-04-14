/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:23:29 by assabich          #+#    #+#             */
/*   Updated: 2025/04/07 16:56:41 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_textures(t_game *game)
{
	int	img_width;
	int	img_height;

	game->img_floor = mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm",
			&img_width, &img_height);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm",
			&img_width, &img_height);
	game->img_player = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm",
			&img_width, &img_height);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx,
			"assets/collectible.xpm", &img_width, &img_height);
	game->img_exit = mlx_xpm_file_to_image (game->mlx, "assets/exit.xpm",
			&img_width, &img_height);
	game->img_enemy = mlx_xpm_file_to_image (game->mlx, "assets/enemy.xpm",
			&img_width, &img_height);
}

void	set_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				game->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	put_imgs_to_win(int x, int y, t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->img_floor, x * TILE_SIZE, y * TILE_SIZE);
	if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_exit, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_player, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == 'N')
		mlx_put_image_to_window(game->mlx, game->win,
			game->img_enemy, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			put_imgs_to_win(x, y, game);
			x++;
		}
		y++;
	}
}

void	render_tile(t_game *game, int x, int y)
{
	void	*img;

	if (game->map[y][x] == '1')
		img = game->img_wall;
	else if (game->map[y][x] == 'C')
		img = game->img_collectible;
	else if (game->map[y][x] == 'E')
		img = game->img_exit;
	else if (game->map[y][x] == 'N')
		img = game->img_enemy;
	else
		img = game->img_floor;
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:11:31 by assabich          #+#    #+#             */
/*   Updated: 2025/03/28 12:35:19 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	display_large_text(t_game *game, int x, int y, char *str)
{
	int	color;

	color = 0x512a21;
	mlx_string_put(game->mlx, game->win, x, y, 0xffffff, str);
	mlx_string_put(game->mlx, game->win, x + 1, y, color, str);
	mlx_string_put(game->mlx, game->win, x, y + 1, color, str);
	mlx_string_put(game->mlx, game->win, x + 1, y + 1, 0xffffff, str);
	free(str);
}

void	update_player_position(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->map_height)
	{
		while (x < game->map_width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		game->img_player,
		game->player_x * TILE_SIZE,
		game->player_y * TILE_SIZE);
}

int	is_valid_move(t_game *game, int x, int y)
{
	return (y >= 0 && y < game->map_height
		&& x >= 0 && x < game->map_width
		&& game->map[y][x] != '1');
}

void	move_player(t_game *game, int new_x, int new_y)
{
	static int	move;

	if (is_valid_move(game, new_x, new_y))
	{
		if (game->map[new_y][new_x] == 'C')
		{
			game->collects--;
			if (!game->collects)
				game->exit_open = true;
		}
		if (game->map[game->player_y][game->player_x] != 'E')
				game->map[game->player_y][game->player_x] = '0';
		render_tile(game, game->player_x, game->player_y);
		game->player_x = new_x;
		game->player_y = new_y;
	}
	update_player_position(game);
	display_large_text(game, 10, 10, ft_itoa(move++));
	check_end(game, new_x, new_y, move);
	ft_printf("moves: %d\n", move);
}

int	handle_key(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == XK_Escape)
		exit_game(game);
	else if (keycode == XK_w || keycode == XK_Up)
		new_y--;
	else if (keycode == XK_s || keycode == XK_Down)
		new_y++;
	else if (keycode == XK_a || keycode == XK_Left)
		new_x--;
	else if (keycode == XK_d || keycode == XK_Right)
		new_x++;
	move_player(game, new_x, new_y);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:09:04 by assabich          #+#    #+#             */
/*   Updated: 2025/03/28 12:36:00 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_char(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E' || c == 'N')
		return (1);
	return (0);
}

void	free_map(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	exit_game(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_enemy)
		mlx_destroy_image(game->mlx, game->img_enemy);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->map)
		free_map(game, game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (exit(0), 0);
}

void	check_end(t_game *game, int new_x, int new_y, int move)
{
	if (game->map[new_y][new_x] == 'E' &&
		game->collects == 0 && game->exit_open)
	{
		ft_printf("Congrats: You won with %d moves!\n", move);
		exit_game(game);
	}
	if (game->map[new_y][new_x] == 'N')
	{
		ft_printf("You loose ! :( \n");
		exit_game(game);
	}
}

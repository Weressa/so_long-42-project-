/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:33:03 by assabich          #+#    #+#             */
/*   Updated: 2025/04/09 10:47:49 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf("Error: Please choose a map !\n"), 1);
	if (ft_strncmp(".ber", &argv[1][ft_strlen(argv[1]) - 4], 4) != 0)
		return (ft_printf("Error: Please choose a map.ber !\n"), 1);
	if (!read_map(argv[1], &game))
		return (1);
	if (!parse_map(&game))
		return (free_map(&game, game.map), 1);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 64 * game.map_width,
			64 * game.map_height, "so_long");
	game.exit_open = false;
	load_textures(&game);
	render_map(&game);
	set_player_position(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
	return (0);
}

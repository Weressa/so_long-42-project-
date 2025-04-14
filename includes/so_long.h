/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:16:47 by assabich          #+#    #+#             */
/*   Updated: 2025/03/28 12:41:12 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// standard libraries
# include <stdlib.h>
# include <unistd.h> 
# include <fcntl.h> 
# include <stdio.h> 
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdbool.h>

//custom libraries
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define WIDTH 
# define HEIGHT 
# define TILE_SIZE 64

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_height;
	int		map_width;
	void	*img_wall;
	void	*img_floor;
	void	*img_collectible;
	void	*img_exit;
	void	*img_player;
	void	*img_enemy;
	int		player_x;
	int		player_y;
	int		collects;
	int		player;
	int		exit;
	int		enemy;
	bool	exit_open;
}	t_game;

int		read_map(char *file, t_game *game);
int		check_char(char c);
int		parse_map(t_game *game);
int		is_accessible(t_game *game);
void	load_textures(t_game *game);
void	render_map(t_game *game);
void	set_player_position(t_game *game);
void	render_tile(t_game *game, int x, int y);
int		handle_key(int keycode, t_game *game);
int		exit_game(t_game *game);
void	update_player_position(t_game *game);
void	free_map(t_game *game, char **map);
int		exit_game(t_game *game);
void	check_end(t_game *game, int new_x, int new_y, int move);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 01:03:45 by assabich          #+#    #+#             */
/*   Updated: 2025/03/28 12:06:06 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_rectangle(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		if ((int)(ft_strlen(game->map[i]) - 1) != game->map_width)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if ((i == 0 || i == game->map_height - 1) && game->map[i][j] != '1')
				return (0);
			else if ((j == 0 || j == game->map_width - 1)
				&& game->map[i][j] != '1')
				return (0);
			else if (!check_char(game->map[i][j]) && i != 0
				&& i != game->map_height - 1 && j != 0
				&& j != game->map_width - 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	count_elements(int i, int j, t_game *game)
{
	if (game->map[i][j] == 'P')
		game->player++;
	else if (game->map[i][j] == 'E')
		game->exit++;
	else if (game->map[i][j] == 'N')
		game->enemy++;
	else if (game->map[i][j] == 'C')
		game->collects++;
}

int	correct_elements(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->player = 0;
	game->exit = 0;
	game->collects = 0;
	game->enemy = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			count_elements(i, j, game);
			j++;
		}
		i++;
	}
	if (game->player != 1 || game->exit != 1 || game->collects < 1)
		return (0);
	return (1);
}

int	parse_map(t_game *game)
{
	if (!is_rectangle(game))
	{
		ft_putstr_fd("Error: Map is not rectangle\n", 2);
		return (0);
	}
	if (!is_valid(game))
	{
		ft_putstr_fd("Error: Map is not surrounded by walls !\n", 2);
		return (0);
	}
	if (!correct_elements(game))
	{
		ft_putstr_fd("Error: Incorrect nomber of elements\n", 2);
		return (0);
	}
	if (!is_accessible(game))
	{
		ft_putstr_fd("Error: Map is not playable\n", 2);
		return (0);
	}
	return (1);
}

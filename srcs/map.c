/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assabich <assabich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:57:00 by assabich          #+#    #+#             */
/*   Updated: 2025/03/24 17:39:54 by assabich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open (file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	close (fd);
	return (count);
}

//free the created lines
static void	free_maps(char **map, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	create_map(int fd, char **map, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
		{
			get_next_line(-1);
			close(fd);
			free_maps(map, i);
			free(map);
			return (0);
		}
		i++;
	}
	map[i] = NULL;
	return (1);
}

int	read_map(char *file, t_game *game)
{
	int	fd;
	int	lines;

	lines = count_lines(file);
	if (lines <= 0)
		return (ft_printf("Error: unable to read lines.\n"), 0);
	game->map = malloc (sizeof(char *) * (lines + 1));
	if (!game->map)
		return (ft_printf("Error: failed to malloc map.\n"), 0);
	fd = open (file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error: failed to open file.\n"), 0);
	if (!create_map(fd, game->map, lines))
		return (ft_printf("Error: failed to create map.\n"), 0);
	close (fd);
	get_next_line(-1);
	game->map_height = lines;
	game->map_width = ft_strlen(game->map[0]) - 1;
	return (1);
}

#include "../so_long.h"

static int	width_of_map(char *string)
{
	int	width;

	width = 0;
	while (string[width] != '\0')
		width++;
	if (string[width - 1] == '\n')
		width--;
	return (width);
}

static int	add_line(t_idk *game, char *line)
{
	char	**temporary;
	int		i;

	if (!line)
		return (0);
	i = 0;
	game->heightmap++;
	temporary = (char **)malloc(sizeof(char *) * (game->heightmap + 1));
	if(!temporary)
		return (0);
	temporary[game->heightmap] = NULL;
	while (i < game->heightmap - 1)
	{
		temporary[i] = game->map[i];
		i++;
	}
	temporary[i] = line;
	if (game->map != NULL)
		game->map = NULL;
	game->map = temporary;
	return (1);
}

int	map_reading(t_idk *game, char **argv)
{
	char	*readmap;

	readmap = NULL;
	game->fd = open(argv[1], O_RDONLY);
	if (game->fd < 0)
	{
		ft_printf("erro");
		return (0);
	}
	while (1)
	{
		readmap = get_next_line(game->fd);
		if (!add_line(game, readmap))
			break ;
	}
	close (game->fd);
	if (!game->map || !game->map[0])
        return (0);
	game->widthmap = width_of_map(game->map[0]);
	return (1);
}
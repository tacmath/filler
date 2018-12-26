int main(void)
{
	char *line;
	char player;
	int mapx;
	int mapy;
	char **map;
	int n;

	n = -1;
	get_next_line(0, &line);
	if (line[10] == '1')
		player = 'o';
	else if (line[10] == '2')
		player = 'x';
	while (ft_strncmp(line, "Plateau", 7))
	{
		free(line);
		get_next_line(0, &line);
	}
	mapy = ft_atoi(&(line[8]));
	mapx = ft_atoi(&(line[11]));
	free(line);
	get_next_line(0, &line);
	free(line);
	map = malloc(sizeof(char*) * mapy); //protege
	while (++n < mapy)
	{
		get_next_line(0, &line);
		map[n] = ft_strdup(&(line[4]));
		free(line);
	}
	return (0);
}

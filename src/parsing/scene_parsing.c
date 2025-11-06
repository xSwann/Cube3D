#include "../../headers/cube3D.h"

void	error_handler(char *error_message)
{
	printf("%s", error_message);
	exit(EXIT_FAILURE);

}

/* void	fill_texture_and_colors(t_scene *scene, char *scene_line)
{

} */

char *import_color_line(char *line)
{
	int i;
	int first_number;
	int count;
	int coma_count;

	i = 0;
	count = 0;
	first_number = 0;
	coma_count = 0;
	while(line[i] && coma_count < 3)
	{
		first_number = i;
		count = 0;
		while(line[i] && ft_isdigit(line[i]))
		{
			i++;
			count++;
		}
		if(count == 0 || (line[i] != ',' && coma_count < 2) || (count > 3) || (ft_atoi(ft_substr(line, first_number, i)) > 255))
			error_handler("Error:\nFloor and Ceilling color must be inside 0 and 255 separated by ','");
		i++;
		coma_count++;
	}
	printf("GG\n");
	return ("DD");
	//return (sanitize_line(line));
}

void	import_configuration_line(char *line, t_scene *scene)
{
	int i;

	i = 0;
	while(line[i] && (line[i] == ' '))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
	{
		if(line[i] == 'F')
		{
			i++;
			while(line[i] == ' ')
				i++;
			scene->floor_color = import_color_line(line + i);
		}
		if(line[i] == 'C')
		{
			i++;
			while(line[i] == ' ')
				i++;
			scene->ceiling_color = import_color_line(line + i);
		}
		return;
	}
	error_handler("Need configurations lines before the map\n");

}

void	read_scene_lines(int fd, t_scene *scene)
{
	char	*scene_line;

	(void)scene;
	scene_line = "debut";
	while (scene_line)
	{
		//fill_texture_and_colors(scene, scene_line);
		scene_line = get_next_line(fd);
		if (scene_line && scene_line[0] != '\n')
		{
			import_configuration_line(scene_line, scene);
			printf("%s", scene_line);
		}
	}
	free(scene_line);
}

t_scene	read_scene(char *scene_name)
{
	int		fd;
	t_scene	scene;

	fd = open(scene_name, O_RDONLY);
	if (fd < 0)
	{
		printf("File does not exit");
		exit(EXIT_FAILURE);
	}
	read_scene_lines(fd, &scene);
	return (scene);
}

t_scene parse_file(char *file_name)
{
    t_scene scene;

	scene = read_scene(file_name);
    return (scene);
}


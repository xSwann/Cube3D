
#include "../../headers/cube3D.h"

void get_width_and_height(char **raw_map, t_scene *scene)
{
    int height;
    int width;
    int old_width;

    height = 0;
    width = 0;

    while(raw_map[height])
    {
        old_width = 0;
        while (raw_map[height][old_width])
            old_width++;
        if (old_width > width)
            width = old_width;
        height++;
    }
    scene->map_width = width;
    scene->map_height = height;
}
//Uniform the map, all lines are the same len and void are replaced by ' '
char **uniform_map(char **map, int width, int height)
{
    char **square_map;
    int i;
    int j;

    i = 0;
    j = 0;
    square_map = malloc(sizeof(char *) * (height + 1));
    if (!square_map)
        error_handler("Memory allocation failed");
    square_map[height] = 0;
    while (i < height)
    {
        j = 0;
        square_map[i] = malloc(sizeof(char) * (width + 1));
        if (!square_map[i])
            error_handler("Memory allocation failed");
        square_map[i][width] = '\0';
        while(j < width)
        {
            if (j < ft_strlen(map[i]))
                square_map[i][j] = map[i][j];
            else
            square_map[i][j] = ' ';
            j++;
        }
        i++;
    }
    return (square_map);
}

void    validate_map(t_scene *scene)
{

    int i;
    
    i = 0;
    (void)scene;
    /* while(square_map[i])
    {
        printf("%s", square_map[i]);
        i++;
    } */
    /* int i;
    int void_start;
    int void_end;

    i = 0;
    if (!is_wall_line(scene->map_tab[0]))
        error_handler("Map must be bordered by walls");
    while(scene->map_tab[i])
    {

        i++;
    }
    if (!is_wall_line(scene->map_tab[0]))
        error_handler("Map must be bordered by walls");
        */
}

//recuperer la plus grande ligne et mettre des void pour faire une map carre
//checker sur une ligne si les case en dessous void sont des 1
//is_wall_line doit verifier si la ligne est compose de 1 ou de void
//liste chainee qui contient lemplacement des void et checker la prochaine ligne si ces endroit sont complete soit par 1 soit par void
//si la len est plus grande que lanmcienne ligne verifier que de la len de lenciennt ligne jusquq la fin il y ai des 1
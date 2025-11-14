
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
//Verifie que la map soit entourree de murs
//Pour l'instant n'accepte pas les trous (espaces vides) a l'interieur des murs
void    validate_map(char **map, int width, int height)
{

    int i;
    int j;
    
    i = 0;
    while (map[i])
    {
        j = 0;
        while(j < width)
        {
            if (j < width && map[i][j] == '0')
            {
                if (j > 0 && map[i][j - 1] != '1')
                    error_handler("1: Map must be bordered by walls");
                while(j < width && map[i][j] != ' ')
                    j++;
                if (j > 0 && map[i][j - 1] != '1')
                    error_handler("2: Map must be bordered by walls");
            }
            j++;
        }
        i++;
    }
    i = 0;
    j = 0;
    while(j < width)
    {
        i = 0;
        while (map[i])
        {
            if (j < width && map[i][j] == '0')
            {
                if (i > 0 && map[i - 1][j] != '1')
                    error_handler("3: Map must be bordered by walls");
                while(map[i] && map[i][j] != ' ')
                    i++;
                if (i > 0 && map[i - 1][j] != '1')
                    error_handler("4: Map must be bordered by walls");
            }
            if (i < height)
                i++;
        }
        j++;
    }
}

//checker sur une ligne si les case en dessous void sont des 1 ou des void
//is_wall_line doit verifier si la ligne est compose de 1 ou de void
//liste chainee qui contient lemplacement des void et checker la prochaine ligne si ces endroit sont complete soit par 1 soit par void
//si la len est plus grande que lanmcienne ligne verifier que de la len de lenciennt ligne jusquq la fin il y ai des 1
#include "../../headers/cube3D.h"

void    flood(t_scene *scene, t_fill *f, int x, int y)
{
    char tile;

    if (x < 0 || y < 0 || x >= f->width || y >= f->height)
        return ;
    if (f->visited[y][x] == 1)
        return ;
    tile = f->map[y][x];
    if (tile == '1')
        return ;
    if (is_open_tile(tile))
        free_scene_and_exit(scene, "Map is not closed by walls");
    f->visited[y][x] = 1;

    flood(scene, f, x + 1, y);
    flood(scene, f, x - 1, y);
    flood(scene, f, x, y + 1);
    flood(scene, f, x, y - 1);
}



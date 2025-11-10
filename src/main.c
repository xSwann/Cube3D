#include "../headers/cube3D.h"

int main(int argc, char **argv)
{
    t_scene scene;

    (void)argc;
    scene = parse_file(argv[1]);
    free_scene(&scene);
    return (0);
}
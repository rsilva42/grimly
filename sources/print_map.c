#include "grimly.h"

void print_map(t_mapinfo *map) {
    if (map && map->map)
        for (size_t i = 0; i < map->height; i++)
            printf("%s\n", (map->map)[i]);
}
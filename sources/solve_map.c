#include "grimly.h"

t_mapnode *new_mapnode(size_t x, size_t y, t_mapnode *root) {
    t_mapnode *new = malloc(sizeof(t_mapnode));

    new->x = x;
    new->y = y;
    new->root = root;

    return new;
}

t_mapnode *find_start(t_mapinfo *map) {
    for(size_t y = 0; y < map->height; y++)
        for(size_t x = 0; x < map->width; x++)
            if (map->map[y][x] == map->start)
                return new_mapnode(x, y, NULL);

    return NULL;
}

char **make_visited_map(t_mapinfo *map) {
    char **visited = malloc(sizeof(char *) * map->height);

    for(size_t i = 0; i < map->height; i++) {
        visited[i] = malloc(sizeof(char) * map->width);
        for(size_t k = 0; k < map->width; k++)
            visited[i][k] = 0;
    }

    return visited;
}

int solve_map(t_mapinfo *map) {
    char **visited = make_visited_map(map);
    t_mapnode *start = find_start(map);

    t_queue *head = new_queue_node(start, NULL, NULL);
    visited[start->y][start->x] = 1;

    t_mapnode *node = NULL;

    while (head) {
        node = dequeue(&head);

        // break when end is found
        if (map->map[node->y][node->x] == map->end)
            break;

        // check top
        if (node->y > 0 && !(visited[node->y - 1][node->x]) && map->map[node->y - 1][node->x] != map->full) {
            enqueue(&head, new_mapnode(node->x, node->y - 1, node));
            visited[node->y - 1][node->x] = 1;
        }
        
        // check left
        if (node->x > 0 && !(visited[node->y][node->x - 1]) && map->map[node->y][node->x - 1] != map->full) {
            enqueue(&head, new_mapnode(node->x - 1, node->y, node));
            visited[node->y][node->x - 1] = 1;
        }
        
        // check right
        if (node->x + 1 < map->width && !(visited[node->y][node->x + 1]) && map->map[node->y][node->x + 1] != map->full) {
            enqueue(&head, new_mapnode(node->x + 1, node->y, node));
            visited[node->y][node->x + 1] = 1;
        }
        
        // check bottom
        if (node->y + 1 < map->height && !(visited[node->y + 1][node->x]) && map->map[node->y + 1][node->x] != map->full) {
            enqueue(&head, new_mapnode(node->x, node->y + 1, node));
            visited[node->y + 1][node->x] = 1;
        }
    }

    //if end not found
    if (map->map[node->y][node->x] != map->end)
        return 0;

    int steps = 0;
    while (node) {
        if (map->map[node->y][node->x] != map->start && map->map[node->y][node->x] != map->end) {
            map->map[node->y][node->x] = map->path;
            steps++;
        }
        node = node->root;
    }

    return steps;
}

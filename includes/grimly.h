#ifndef GRIMLY_H
# define GRIMLY_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

# define MIN_INFO_LEN 8
# define MAX_MAP_SIZE 1000000000

typedef struct  s_mapinfo {
    size_t height;
    size_t width;
    char full;
    char empty;
    char path;
    char start;
    char end;
    char **map;
}               t_mapinfo;

typedef struct  s_mapnode {
    size_t x;
    size_t y;
    struct s_mapnode *root;
}               t_mapnode;

typedef struct  s_queue {
    t_mapnode *node;
    struct s_queue *prev;
    struct s_queue *next;
}               t_queue;

// for debugging
// in read_map.c
void print_mapinfo(t_mapinfo *map);

// queue.c
t_queue *new_queue_node(t_mapnode *node, t_queue *prev, t_queue *next);
t_mapnode *dequeue(t_queue **head);
void enqueue(t_queue **head, t_mapnode *to_push);

// read_map.c
t_mapinfo *read_map(char *mapname);

// solve_map.c
int solve_map(t_mapinfo *map);

//print_map.c
void print_map(t_mapinfo *map);

#endif

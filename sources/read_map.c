#include "grimly.h"

// debug function
void print_mapinfo(t_mapinfo *map) {
	printf("full:\t%c\nempty:\t%c\npath:\t%c\nstart:\t%c\nend:\t%c\n",
		map->full, map->empty, map->path, map->start, map->end);
	printf("height:\t%ld\nwidth:\t%ld\n", map->height, map->width);
	printf("map:\t%p\n", map->map);
}

void    free_map(char **map, size_t rows) {
    for (size_t i = 0; i < rows; i++)
        free(map[i]);
    free(map);
}

// returns zero on success non-zero value on error
int    parse_map_header(t_mapinfo *map, FILE *file) {
    size_t buffer_size = 0;
    char *buffer = NULL;
    int line_len;

    // read first line:
    line_len = getline(&buffer, &buffer_size, file);
    if (line_len < MIN_INFO_LEN) {
        //error out
        fprintf(stderr, "first line is missing information (line too short).\n");
        free(buffer);
        return 1;
    }

    // last 5 characters are assumed to be the characters that make up the map
    // "- 6" offset accounts for the newline at the end
    char *info_ptr = buffer + line_len - 6;

    map->full = info_ptr[0];
    map->empty = info_ptr[1];
    map->path = info_ptr[2];
    map->start = info_ptr[3];
    map->end = info_ptr[4];

    //truncate the characters
    info_ptr[0] = '\0';

    //split at the x
    char *dimension = strtok(buffer, "x");

    //check for invalid chars in dimension
    for (int i = 0; dimension[i]; i++)
        if (dimension[i] < '0' || dimension[i] > '9') {
            fprintf(stderr, "invalid character in dimensions\n");
            free(buffer);
            return 1;
        }

    map->height = atoi(dimension);
    dimension = strtok(NULL, "");
    for (int i = 0; dimension[i]; i++)
        if (dimension[i] < '0' || dimension[i] > '9') {
            fprintf(stderr, "invalid character in dimensions\n");
            free(buffer);
            return 1;
        }
    map->width = atoi(dimension);

    if (!map->height)
        fprintf(stderr, "invalid height\n");
    
    if (!map->width)
        fprintf(stderr, "invalid width\n");

    if (strtok(NULL, "x"))
        fprintf(stderr, "too many dimensions found\n");

    if (map->height * map->width > MAX_MAP_SIZE)
        fprintf(stderr, "map is too big, max size is: %d tiles\n", MAX_MAP_SIZE);

    free(buffer);
    return 0;
}

// returns zero on success non-zero value on error
int    parse_map(t_mapinfo *map, FILE *file) {

    size_t line_index = 0;
    map->map = malloc(sizeof(char *) * map->height);

    size_t line_len = 0;
    int start_count = 0;
    int end_count = 0;

    // read the map out:
    while (line_index <= map->height && getline(&map->map[line_index], &line_len, file) != -1) {
        size_t i;
        for (i = 0; map->map[line_index][i] && map->map[line_index][i] != '\n'; i++) {
            if (map->map[line_index][i] != map->full
                && map->map[line_index][i] != map->empty
                && map->map[line_index][i] != map->path
                && map->map[line_index][i] != map->start
                && map->map[line_index][i] != map->end) {
                    fprintf(stderr, "invalid character in line %ld\n", line_index + 2);
                    return 1;
            } else if (map->map[line_index][i] == map->start) {
                start_count++;
            } else if (map->map[line_index][i] == map->end) {
                end_count++;
            }
        }

        // truncate newlines at the end
        if (map->map[line_index][i] == '\n')
            map->map[line_index][i] = '\0';

        if (i < map->width) {
            fprintf(stderr, "width of line %ld is too short, expected %ld got %ld\n", line_index + 1, map->width, i);
            free_map(map->map, line_index + 1);
            printf("line index:\t%ld\n", line_index);
            return 1;
        } else if (i > map->width) {
            fprintf(stderr, "width of line %ld is too long, expected %ld got %ld\n", line_index + 1, map->width, i);
            free_map(map->map, line_index + 1);
            printf("line index:\t%ld\n", line_index);
            return 1;
        }
        // printf("%p:\n%s", map->map[line_index], map->map[line_index]);

        line_len = 0;
        line_index++;
    }
    // printf("line count:\t%ld\n", line_index);

    if (line_index != map->height) {
        fprintf(stderr, "map height did not match header\n");
        free_map(map->map, line_index + 1);
        return 1;
    }

    if (start_count < 1) {
        fprintf(stderr, "missing start\n");
        free_map(map->map, line_index + 1);
        return 1;
    } else if (start_count > 1) {
        fprintf(stderr, "too many start points, only one allowed\n");
        free_map(map->map, line_index + 1);
        return 1;
    }

    if (end_count == 0) {
        fprintf(stderr, "no exit found\n");
        free_map(map->map, line_index + 1);
        return 1;
    }

    return 0;
}

t_mapinfo *read_map(char *mapname) {
    t_mapinfo *map = malloc(sizeof(t_mapinfo));
    FILE *file;

    if (!(file = fopen(mapname, "r"))) {
        perror("error opening file");
        return NULL;
    }

    if (parse_map_header(map, file))
        return NULL;

    if (parse_map(map, file))
        return NULL;

    return map;
}
#include "grimly.h"

void grimly(char *mapname) {
	t_mapinfo *map;
	int steps;

	map = read_map(mapname);

	if (map == NULL) {
		fprintf(stderr, "error reading map\n");
		return;
	}

	steps = solve_map(map);

	if (steps) {
		printf("%ldx%ld%c%c%c%c%c\n",
			map->height, map->width, map->full, map->empty, map->path, map->start, map->end);
		print_map(map);
		printf("RESULT IN %d STEPS\n", steps);
	} else {
		fprintf(stderr, "no solution found\n");
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "not enough arguments\n");
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; i++)
		grimly(argv[i]);

	return EXIT_SUCCESS;
}

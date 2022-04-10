NAME = grimly

CCFLAGS = -c -Wall -Wextra -Werror

SRCS = sources/grimly.c\
		sources/queue.c\
		sources/read_map.c\
		sources/solve_map.c\
		sources/print_map.c


OBJS = objects/grimly.o\
		objects/queue.o\
		objects/read_map.o\
		objects/solve_map.o\
		objects/print_map.o

INCL = -I includes

all: $(NAME)

objects/%.o: sources/%.c
	@/bin/mkdir -p objects
	@gcc $(CCFLAGS) $(INCL) $< -o $@

$(NAME): $(OBJS)
	@gcc $(OBJS) $(LIB_LINK) -o $(NAME)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
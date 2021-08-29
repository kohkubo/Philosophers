# ***********************************

NAME	= libex.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O2 -g
obj		= $(src:%.c=%.o)

.PHONY: all clean fclean re debug sani-debug

# ***********************************

src =\
	./arraylen.c \
	./contain.c \
	./debug_array.c \
	./free_set.c \
	./free_string_array.c \
	./ft_atol.c \
	./ft_error_exit.c \
	./ft_fatal.c \
	./ft_isspace.c \
	./ft_min_size_t.c \
	./ft_strcmp.c \
	./ft_strndup.c \
	./ft_xcalloc.c \
	./ft_xmalloc.c \
	./ft_xstrdup.c \
	./get_next_line.c \
	./is_space_string.c \
	./print_array.c \
	./random_string.c \
	./spacelen.c \
	./str_arraydup.c \
	./debug_array.c \
	./is_available_pid.c \
	./is_num_string.c \
	./ft_quick_sort.c \

# ***********************************

all: $(NAME)

$(NAME): $(obj)
	$(AR) -rc $(NAME) $(obj)
	ranlib $(NAME)

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# ***********************************

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address"

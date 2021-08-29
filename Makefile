# ***********************************

NAME	= philosophers
includes = -I./includes
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3 $(includes) -g
obj		= $(src:%.c=%.o)

.PHONY: all clean fclean re debug sani-debug

# ***********************************

src =\

# ***********************************

all: $(NAME)

bonus: all

$(NAME): $(obj)
	$(MAKE) -C lib/libft
	$(MAKE) -C lib/libex
	$(CC) $(CFLAGS) $(obj) -o $(NAME) $(flags) ./lib/libft/libft.a ./lib/libex/libex.a

clean:
	$(MAKE) clean -C lib/libex
	$(MAKE) clean -C lib/libft
	$(RM) -rf $(obj)

fclean: clean
	$(MAKE) fclean -C lib/libex
	$(MAKE) fclean -C lib/libft
	$(RM) -rf $(NAME)

re: fclean all

# ***********************************

debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g"

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g -fsanitize=address -fno-omit-frame-pointer"

init:
	zsh header.sh srcs includes/philosophers.h Makefile srcs

# ***********************************

-include $(depends)

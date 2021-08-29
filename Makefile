# ***********************************

NAME	= fractol
includes = -I./includes
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3 $(includes) -MMD -MP -g
obj		= $(src:%.c=%.o)
depends = $(obj:%.o=%.d)

.PHONY: all clean fclean re debug sani-debug

# ***********************************

src =\


# ***********************************

# mlx_dir = ./lib/minilibx
# mlx_name = libmlx.a

uname := $(shell uname)
ifeq ($(uname),Darwin)
	mlx_dir = ./lib/minilibx-linux
	mlx_name = libmlx_Darwin.a
	flags += -L $(mlx_dir) -L/usr/X11R6/lib -lmlx -lX11 -lXext -framework OpenGL -framework AppKit
	CFLAGS += -I$(mlx_dir)
endif
ifeq ($(uname),Linux)
	mlx_dir = ./lib/minilibx-linux
	mlx_name = libmlx.a
	flags += -L $(mlx_dir) -lmlx -lX11 -lXext -lm
	CFLAGS += -I$(mlx_dir)
endif

# ***********************************

all: $(NAME)

bonus: all

$(NAME): $(obj)
	$(MAKE) -C lib/libft
	$(MAKE) -C lib/libex
	$(MAKE) -C $(mlx_dir)
	cp $(mlx_dir)/$(mlx_name) .
	$(CC) $(CFLAGS) $(obj) -o $(NAME) $(flags) ./lib/libft/libft.a ./lib/libex/libex.a

clean:
	$(MAKE) clean -C lib/libex
	$(MAKE) clean -C lib/libft
	$(RM) $(obj) $(depends) libmlx_Darwin.a libmlx.a libmlx.dylib

fclean: clean
	$(MAKE) clean -C $(mlx_dir)
	$(MAKE) fclean -C lib/libex
	$(MAKE) fclean -C lib/libft
	$(RM) $(NAME)

re: fclean all

# ***********************************

debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g"

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g -fsanitize=address -fno-omit-frame-pointer"

init:
	zsh header.sh srcs includes/fract.h Makefile srcs

# ***********************************

-include $(depends)

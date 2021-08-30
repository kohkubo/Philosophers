# ***********************************

.PHONY		: all clean fclean re \
			init \
			norm \
			test \
			leak \

# ***********************************

NAME		= philo
includes	= ./includes ./lib/libex ./lib/libft
src_dir		= srcs
obj_dir		= objs
obj			= $(src:%.c=%.o)

# ***********************************

CC 			= gcc
libs		= -L./lib/libft -L./lib/libex -lft -lex
CFLAGS		= -Wall -Wextra -Werror -O2 -g $(includes:%=-I%)

# ***********************************

src =\
	./srcs/main.c \
	./srcs/util.c \

# ***********************************

lib_dir		= lib
lib			= ./$(libft) \
			./$(libex) \

sharedlib	= ./tests/sharedlib.c

# ****************

libft_dir	= $(lib_dir)/libft
libft		= $(libft_dir)/libft.a

# ****************

libex_dir	= $(lib_dir)/libex
libex		= $(libex_dir)/libex.a

# ***********************************

all			: $(NAME)

$(NAME)		: $(obj) $(lib)
	$(CC) $(CFLAGS) $(obj) -o $(NAME) $(libs)

clean		: lib_clean
	$(RM) $(obj)
	$(RM) -rf $(NAME).dSYM

fclean		: lib_fclean
	$(RM) $(obj)
	$(RM) $(NAME)

re			: fclean all

# ***********************************

init		:
	zsh header.sh srcs includes/philo.h Makefile srcs

test		: $(NAME)
	bash ./tests/test.sh

sani-debug	: fclean lib_sani-debug
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address" $(lib)
	$(MAKE) clean

norm:
	@printf "$(_RED)"; norminette $(src_dir) $(includes) ./lib \
	| grep -v -e ": OK!" -v -e "Missing or invalid header. Header are being reintroduced as a mandatory part of your files. This is not yet an error." \
	&& printf "$(_END)" && exit 1 \
	|| printf "$(_GREEN)%s\n$(_END)" "Norm OK!"

# ***********************************

$(libft): $(libft_dir)/*.c
	$(MAKE) -C $(libft_dir)

$(libex): $(libex_dir)/*.c
	$(MAKE) -C $(libex_dir)

lib_make	:$(libft) $(libex)

lib_clean	:
	$(MAKE) clean -C $(libft_dir)
	$(MAKE) clean -C $(libex_dir)

lib_fclean	:
	$(MAKE) fclean -C $(libft_dir)
	$(MAKE) fclean -C $(libex_dir)

# Colors
# ****************************************************************************

_GREY	= \033[30m
_RED	= \033[31m
_GREEN	= \033[32m
_YELLOW	= \033[33m
_BLUE	= \033[34m
_PURPLE	= \033[35m
_CYAN	= \033[36m
_WHITE	= \033[37m
_END	= \033[0m

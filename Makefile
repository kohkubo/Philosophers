# ***********************************

.PHONY		: all clean fclean re \
			init \
			norm \
			test \
			leak \
			sani-debug \

# ***********************************

NAME		= philo
includes	= ./includes
src_dir		= srcs
obj_dir		= objs
obj			= $(src:%.c=%.o)

# ***********************************

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror -O2 -g $(includes:%=-I%) #-fsanitize=thread

# ***********************************

src =\
	./srcs/libft.c \
	./srcs/main.c \
	./srcs/util.c \
	./srcs/util2.c \

# ***********************************

all			: $(NAME)

$(NAME)		: $(obj) $(lib)
	$(CC) $(CFLAGS) $(obj) -o $(NAME)

clean		:
	$(RM) $(obj)
	$(RM) -rf $(NAME).dSYM

fclean		: clean
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

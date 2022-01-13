SRCS	=	main.c \
			./sources/utils/utils.c \
			./sources/utils/utils01.c \
			./sources/utils/utils02.c \
			./sources/utils/utils03.c \
			./sources/utils/print_utils.c \
			./sources/errors/errors.c \
			./sources/lexer/init_lexer.c \
			./sources/lexer/lexer.c \
			./sources/free/free_lexer.c \
			./sources/redirection/redirection.c \
			./sources/exec/exec.c \
			./sources/test/test.c \
			./sources/built_in/build_in.c \
			./sources/built_in/cd.c \
			./sources/built_in/echo.c \
			./sources/built_in/env.c \
			./sources/built_in/export.c \
			./sources/built_in/pwd.c \
			./sources/built_in/unset.c \
			./sources/built_in/utils_built_in.c \
			./sources/built_in/ctrl_handler.c \
			./sources/built_in/exit.c

OBJS	=	${SRCS:.c=.o}

CC		=	cc -Wall -Werror -Wextra
RM		=	rm -f
NAME	=	minishell

all:		${NAME}

.c.o:
			$(CC) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) -lreadline 

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
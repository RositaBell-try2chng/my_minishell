# Основная директория проекта
SRC_DIR	=	./src/

# Библеотека LibFT
FT_DIR	=	./libft/
FT_LIB	=	$(FT_DIR)libft.a
FT_LNK	=	-L $(FT_DIR) -l ft

# Директория ReadLine
RL_DIR	=	/Users/ztune/.brew/Cellar/readline/8.1.1
#RL_INC	=	-I $(RL_DIR)/include # Закоментировать для Linux
#RL_LIB	=	-L $(RL_DIR)/lib # Закоментировать для Linux

# Параметры сборки и удаления
NAME	=	minishell
SRCS	=	main.c utils.c signals.c puts.c prints.c \
			lexer/lexer.c lexer/parser.c lexer/destroy.c \
			parser/parser.c parser/destroy.c \
			parser/parser_1.c parser/parser_2.c parser/parser_3.c \
			executor/executor_1.c executor/executor_2.c \
			executor/fork.c executor/fork_utils.c \
			commands/cd.c \
			commands/prompt.c \
			commands/pwd.c \
			commands/echo.c \
			commands/env.c \
			commands/export.c \
			commands/unset.c \
			commands/test.c \
			commands/exit.c

OBJS	=	$(addprefix $(SRC_DIR),$(SRCS:.c=.o))
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
RM 		= 	rm -f

all:		$(FT_LIB) $(NAME)

$(SRC_DIR)%.o:$(SRC_DIR)%.c
			$(CC) $(CFLAGS) -I $(FT_DIR) -I $(SRC_DIR) $(RL_INC) -o $@ -c $<

$(FT_LIB):
			make -C $(FT_DIR)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(RL_LIB) -lreadline -lhistory $(OBJS) $(FT_LNK) -lm -o $(NAME)

clean:
			${RM} $(OBJS)
			make -C $(FT_DIR) clean

fclean:
			${RM} $(OBJS)
			make -C $(FT_DIR) fclean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

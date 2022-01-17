NAME	=	libft.a
SRCS	=	ft_strlen.c ft_strcpy.c ft_strcmp.c ft_strdup.c ft_memset.c ft_memcpy.c ft_memjoin.c ft_split.c ft_gnl.c ft_miniglob.c ft_arrayfree.c ft_free.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g
RM 		= 	rm -f

all: 		$(NAME)

%.o:%.c
			$(CC) $(CFLAGS) -I . -o $@ -c $<

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)
			ranlib $(NAME)

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} ${NAME}

re:			fclean $(NAME)

.PHONY:		all clean fclean re

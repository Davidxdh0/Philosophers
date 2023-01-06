# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dyeboa <dyeboa@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/26 15:54:34 by dyeboa        #+#    #+#                  #
#    Updated: 2022/07/20 12:38:56 by dyeboa        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS=		ft_atoi.c \
			ft_atoi_base.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putnbr_fd.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strstr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_strrchr.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_strlcpy.c \
			ft_strchr.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memmove.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_strmapi.c \
			ft_striteri.c \
			get_next_line.c 

SRC_GNL = get_next_line.c get_next_line_utils.c maingnl.c

NAME	= libft.a
OBJS	= $(SRCS:.c=.o)
RM		= rm -f
FLAGS	= -Wall -Wextra -Werror
INCS	= .

.c.o :
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	ar -rcs $(NAME) $(OBJS)

gnl:
	${CC} ${FLAGS} ${SRC_GNL} -D BUFFER_SIZE=100 -o gnl

all: $(NAME)

clean:
	$(RM) -f $(OBJS)
	$(RM) -f $(NAME)
	$(RM) -f gnl

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean
NAME		= 	philosophers
CC 			= 	gcc

CFLAGS 		= 	-Wall -Wextra -Werror
INCLUDE 	= 	./include
VPATH 		= 	src

SRC_FILES 	=	main.c utils.c philo.c init.c

# object files
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT = libft.a

# Default build
all: $(OBJ_DIR) $(NAME)

# obj dir
${OBJ_DIR}	:
				mkdir -p ${OBJ_DIR}

# Build 
${NAME}		: 	${OBJ_FILES} 
				$(CC) $(CFLAGS) $^ -o $@

$(OBJ_FILES): 	$(OBJ_DIR)/%.o : %.c
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				rm -rf ${OBJ_DIR}

fclean		:	clean
				rm -rf ${NAME}

re 			: 	fclean all

.PHONY 		: 	clean fclean all 
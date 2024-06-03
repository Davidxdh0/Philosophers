NAME		= 	philosophers
CC 			= 	gcc

CFLAGS 		= 	-Wall -Wextra -Werror -pthread -Ofast -flto -march=native
CFLAGS		+=	-g -fsanitize=thread 
INCLUDE 	= 	./include
VPATH 		= 	src

SRC_FILES 	=	main.c utils.c philo.c init.c end.c eat_utils.c

# object files
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

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
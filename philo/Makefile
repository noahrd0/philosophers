#	COLORS
NOC         = \033[0m
GREEN       = \033[1;32m
RED         = \033[1;31m
BLUE        = \033[1;34m

#	NAME
NAME=philo

#	PATH
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_DIR = ./includes/

#	SRC
SRC_NAME =	main.c			\
			actions.c		\
			init.c			\
			memory.c		\
			parse_args.c	\
			threads.c		\
			utils.c
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = $(INC_DIR)philosophers.h

#	FILES
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

#	FLAGS
CC = gcc $(CFLAGS) -pthread
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(INC_NAME)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $< -o $@
	@echo "$(GREEN)[>]		$@ created.$(NOC)"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@echo "$(GREEN)[>]		$@ created.$(NOC)"

FORCE:

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(GREEN)[>]		.o files deleted.$(NOC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN)[>]		$(NAME) deleted.$(NOC)"

re: fclean all
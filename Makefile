.PHONY: all, $(NAME), test, clean, fclean, re

NAME= lem-in

CC= cc

CFLAGS+= -Wall -Wextra -Werror

SRC_PATH= src/
INC_PATH= includes/
OBJ_PATH= obj/
LIBFT_PATH= includes/libft/

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
INC_LFT = $(addprefix -I, $(addprefix $(LIBFT_PATH), $(INC_PATH)))

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_NAME = main.c lm_room_arrays.c lm_add_attr.c lm_bfs.c\
		   lm_name_btree.c lm_coord_btree.c

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\n"
	@printf "\033[1m\x1b[36mMaking 42 library...\x1b[0m\n"
	@make -C $(LIBFT_PATH)
	@printf "\033[1m\x1b[36mBuilding lem-in executable...\x1b[0m\n"
	@$(CC) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft $(CFLAGS)
	@printf "\033[1m\x1b[32mReady!\x1b[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(INC) $(INC_LFT) -o $@ -c $< 
	@printf "\033[1m\x1b[33m********\x1b[0m"

test: $(OBJ)
	@printf "\033[1m\x1b[33mRefreshing executable...\n"
	@$(CC) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft $(CFLAGS)
	@printf "\033[1m\x1b[32mReady!\x1b[0m\n"

clean:
	@printf "\033[1m\x1b[31mRemoving object files...\x1b[0m\n"
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_PATH)
	@printf "\033[1m\x1b[36mObject files removed.\x1b[0m\n"

fclean: clean
	@printf "\033[1m\x1b[31mReverting to zero state...\x1b[0m\n"
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@printf "\033[1m\x1b[36mClean.\x1b[0m\n"
	
re: fclean all

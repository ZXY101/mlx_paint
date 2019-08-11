NAME = mlx_paint

LIBFT_PATH = ./libft/

SRC_PATH = ./src/

SRC_NAME =	main.c \
			draw_line.c \
			images.c \
			gfx_utility.c \
			misc.c \
			handle_hooks.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

SRCO = $(patsubst %.c, %.o, $(SRC))

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm
MLX_LFLAGS =  -lmlx -lXext -lX11 -lm

FLAGS = -Wall -Werror -Wextra

all: LIBFT $(NAME)

LIBFT:
	@make -C $(LIBFT_PATH)

$(LIBFT_PATH)libft.a:
	@make -C $(LIBFT_PATH)

$(NAME): $(SRCO) $(LIBFT_PATH)libft.a 
	@gcc $(FLAGS) $(SRCO) -L $(LIBFT_PATH) -lft -o $(NAME) $(MLX_LFLAGS)
	@echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m Created.\033[0m"

$(SRC_PATH)%.o: $(SRC_PATH)%.c includes/fdf.h
	@gcc $(FLAGS) -c $< -o $@

clean:
	@/bin/rm -rf $(SRCO)
	@echo "\033[31mObjects Files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31mRemoved.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m Removed.\033[0m"

re: fclean all

.PHONY: all fclean clean re LIBFT
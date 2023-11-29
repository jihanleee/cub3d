NAME = cub3d

SRC_DIR = ./srcs/

INCLUDE = -I ./minilibx-linux/ -I ./include/ -I ./libft/ -I ./vector/

DIR_MLX = ./minilibx-linux/

LIBMLX = ./minilibx-linux/libmlx_Linux.a

DIR_LIBFT = ./libft/

LIBFT = ./libft/libft.a

SRCS =	./srcs/main.c ./srcs/utils.c ./srcs/validate_file.c ./srcs/validate_map.c ./srcs/flood_fill.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -g -Wextra -Wall #-Werror 

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -Imlx_linux -c $< -o $@

$(LIBFT) :
	@$(MAKE) -C $(DIR_LIBFT)

$(LIBMLX) :
	@$(MAKE) -C $(DIR_MLX)

$(NAME) : $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) -o $(NAME) $(OBJS) -L$(DIR_MLX) -lmlx_Linux $(INCLUDE) -Imlx_linux -lXext -lX11 -lm -lz -L$(DIR_LIBFT) -lft

clean :
	rm -f *.o */*.o 
	@$(MAKE) -C $(DIR_LIBFT) clean
	@$(MAKE) -C $(DIR_MLX) clean

fclean : clean
	rm -f $(NAME) $(LIBFT) $(LIBMLX) $(DIR_MLX)obj/*.o

re : fclean all

.PHONY : clean fclean all re

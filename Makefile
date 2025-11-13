NAME := cub3D

# Compiler & Flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -O2 -g3
CPPFLAGS := -I headers -I src/get_next_line -I minilibx-linux

# MiniLibX
MLX_DIR := minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx.a
LIBS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Dossiers
OBJ_DIR := obj
SRC_DIR := src

LIBFT_DIR    := src/libft/

LIBFT_SRCS   := \
	$(LIBFT_DIR)ft_atoi.c \
	$(LIBFT_DIR)ft_isspace.c \
	$(LIBFT_DIR)ft_itoa.c \
	$(LIBFT_DIR)ft_split.c \
	$(LIBFT_DIR)ft_calloc.c \
	$(LIBFT_DIR)ft_memcpy.c \
	$(LIBFT_DIR)ft_memset.c \
	$(LIBFT_DIR)ft_strchr.c \
	$(LIBFT_DIR)ft_substr.c \
	$(LIBFT_DIR)ft_strlen.c \
	$(LIBFT_DIR)ft_strdup.c \
	$(LIBFT_DIR)ft_strcmp.c \
	$(LIBFT_DIR)ft_strncmp.c \
	$(LIBFT_DIR)ft_strjoin.c \
	$(LIBFT_DIR)ft_memmove.c \
	$(LIBFT_DIR)str_is_num.c \
	$(LIBFT_DIR)ft_isalpha.c \
	$(LIBFT_DIR)ft_isalnum.c \
	$(LIBFT_DIR)ft_isdigit.c \
	$(LIBFT_DIR)ft_strslen.c

# Tous les fichiers sources
SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/get_next_line/get_next_line.c \
	$(SRC_DIR)/parsing/scene_parsing.c \
	$(SRC_DIR)/parsing/map_parsing.c \
	$(LIBFT_SRCS)
	$(SRC_DIR)/init/init.c \
	$(SRC_DIR)/init/mlx_init.c \
	$(SRC_DIR)/render/render.c \
	$(SRC_DIR)/render/get_color.c \
	$(SRC_DIR)/events/move.c \
	$(SRC_DIR)/utils/error.c \
	$(SRC_DIR)/utils/free.c \
	$(SRC_DIR)/utils/utils.c \

# Objets
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Couleurs
GREEN := \033[1;32m
BLUE := \033[1;34m
YELLOW := \033[1;33m
RESET := \033[0m

# Règles
all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking:$(RESET) $@"
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
	@echo "$(GREEN)Build complete! $(RESET)"

$(MLX_LIB):
	@echo "$(YELLOW)Building MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)MiniLibX OK$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling:$(RESET) $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

run: all
	@echo "$(YELLOW)Launching cub3D...$(RESET)"
	@./$(NAME) maps/map1.cub

clean:
	@echo "$(YELLOW)Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(YELLOW)Removing binary...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all run clean fclean re
-include $(DEPS)

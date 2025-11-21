NAME := cub3D

# Compiler & Flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -O2 -g3
CPPFLAGS := -I headers -I src/get_next_line -I minilibx-linux

# MiniLibX
MLX_DIR := minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx.a
LIBS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Directories
SRC_DIR := src
OBJ_DIR := obj

### ───────────── LIBFT SOURCES ───────────── ###

LIBFT_DIR := $(SRC_DIR)/libft

LIBFT_SRCS := \
	$(LIBFT_DIR)/ft_atoi.c \
	$(LIBFT_DIR)/ft_isspace.c \
	$(LIBFT_DIR)/ft_itoa.c \
	$(LIBFT_DIR)/ft_split.c \
	$(LIBFT_DIR)/ft_calloc.c \
	$(LIBFT_DIR)/ft_memcpy.c \
	$(LIBFT_DIR)/ft_memset.c \
	$(LIBFT_DIR)/ft_strchr.c \
	$(LIBFT_DIR)/ft_substr.c \
	$(LIBFT_DIR)/ft_strlen.c \
	$(LIBFT_DIR)/ft_strdup.c \
	$(LIBFT_DIR)/ft_strcmp.c \
	$(LIBFT_DIR)/ft_strncmp.c \
	$(LIBFT_DIR)/ft_strjoin.c \
	$(LIBFT_DIR)/ft_memmove.c \
	$(LIBFT_DIR)/str_is_num.c \
	$(LIBFT_DIR)/ft_isalpha.c \
	$(LIBFT_DIR)/ft_isalnum.c \
	$(LIBFT_DIR)/ft_isdigit.c \
	$(LIBFT_DIR)/ft_strslen.c \
	$(LIBFT_DIR)/put_list_in_tab.c 

### ───────────── PROJECT SOURCES ───────────── ###

SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/get_next_line/get_next_line.c \
	$(SRC_DIR)/parsing/read_and_parse.c \
	$(SRC_DIR)/parsing/read_scene.c \
	$(SRC_DIR)/parsing/scene_parsing.c \
	$(SRC_DIR)/parsing/map_parsing.c \
	$(SRC_DIR)/parsing/flood_fill.c \
	$(SRC_DIR)/parsing/parse_texture.c \
	$(SRC_DIR)/parsing/utils/utils.c \
	$(SRC_DIR)/parsing/utils/utils2.c \
	$(SRC_DIR)/parsing/utils/check_utils.c \
	$(SRC_DIR)/parsing/utils/check_utils2.c \
	$(SRC_DIR)/parsing/parse_colors.c \
	$(SRC_DIR)/parsing/utils/print.c \
	$(SRC_DIR)/init/init.c \
	$(SRC_DIR)/init/init2.c \
	$(SRC_DIR)/init/mlx_init.c \
	$(SRC_DIR)/render/render.c \
	$(SRC_DIR)/render/render2.c \
	$(SRC_DIR)/render/get_color.c \
	$(SRC_DIR)/events/move.c \
	$(SRC_DIR)/events/move2.c \
	$(SRC_DIR)/utils/error.c \
	$(SRC_DIR)/utils/free.c \
	$(SRC_DIR)/utils/free2.c \
	$(SRC_DIR)/utils/utils.c \
	$(LIBFT_SRCS)

### ───────────── OBJECTS ───────────── ###

OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

### ───────────── COLORS ───────────── ###

GREEN := \033[1;32m
BLUE := \033[1;34m
YELLOW := \033[1;33m
RESET := \033[0m

### ───────────── RULES ───────────── ###

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking:$(RESET) $@"
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
	@echo "$(GREEN)Build OK !"
	@echo ' ____ ____ ____ ____ ____ ____ ____ '
	@echo '||C |||U |||B |||E |||  |||3 |||D ||'
	@echo '||__|||__|||__|||__|||__|||__|||__||'
	@echo '|/__\|/__\|/__\|/__\|/__\|/__\|/__\|'
	@echo '                                    '
$(MLX_LIB):
	@echo "$(YELLOW)Building MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null
	@echo "$(GREEN)MiniLibX OK$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling:$(RESET) $<"
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -c $< -o $@

run: all
	./$(NAME) maps/map1.cub

clean:
	@echo "$(YELLOW)Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null

fclean: clean
	@echo "$(YELLOW)Removing binary...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run
-include $(DEPS)

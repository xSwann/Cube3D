# =========================
#         cube3D
# =========================

# ---- Binary ----
NAME        := cub3D

# ---- Compiler & Flags ----
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -O2 -g3
CPPFLAGS    := -MMD -MP -I headers -I src/get_next_line -I minilibx-linux

# ---- MiniLibX (Linux) ----
MLX_DIR     := minilibx-linux
MLX_LIB     := $(MLX_DIR)/libmlx.a
LIBS        := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# ---- Sources ----

# ---- Libft ----
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

SRCS        := \
	src/main.c \
	src/get_next_line/get_next_line.c \
	src/parsing/scene_parsing.c \
	src/parsing/map_parsing.c \
	$(LIBFT_SRCS)


# ---- Objects / Deps ----
OBJ_DIR     := obj
OBJS        := $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

# ---- Colors ----
GREEN       := \033[1;32m
BLUE        := \033[1;34m
YELLOW      := \033[1;33m
RESET       := \033[0m

# =========================
#         Rules
# =========================

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	@echo "$(BLUE)Linking:$(RESET) $@"
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
	@echo "$(GREEN)Build complete.$(RESET)"

$(MLX_LIB):
	@echo "$(YELLOW)Building MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null
	@echo "$(GREEN)MiniLibX ready.$(RESET)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling:$(RESET) $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

run: $(NAME)
	@echo "$(YELLOW)Running cube3D...$(RESET)"
	@./$(NAME) maps/map1.cub

debug: CFLAGS := -Wall -Wextra -Werror -g3 -O0
debug: re

asan: CFLAGS := -Wall -Wextra -Werror -g3 -O0 -fsanitize=address
asan: LIBS += -fsanitize=address
asan: re

clean:
	@echo "$(YELLOW)Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null

fclean: clean
	@echo "$(YELLOW)Removing binary...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all run debug asan clean fclean re

-include $(DEPS)

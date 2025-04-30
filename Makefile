### PROGRAM NAME ###
NAME		:= cub3D
ICON		:= 🧍‍♂️

### UTILS ###
CC 			:= clang
CFLAGS 		:= -Wall -Wextra -Werror -g3
DEP_FLAGS	:= -MMD -MP
MAKE_FLAG 	:= --no-print-directory --silent
RM 			:= rm -rf

### COLORS ###
DEFAULT    	:= \033[0m
BLACK    	:= \033[0;30m
RED        	:= \033[0;31m
DRED		:= \033[0;31;5m
GREEN    	:= \033[0;32m
UGREEN    	:= \033[4;32m
YELLOW    	:= \033[;33m
BLUE    	:= \033[0;34m
PURPLE    	:= \033[0;35m
CYAN    	:= \033[0;36m
BWHITE    	:= \033[1;37m
NEW			:= \r\033[K

### DIRECTORIES ###
LIBFT_DIR 	:= lib/libft
MLX_DIR		:= lib/minilibx-linux
SRC_DIR 	:= src
INCLD_DIR 	:= include
OBJS_DIR 	:= objs


### FILES ###
define INCLUDES	:=
	$(INCLD_DIR)/
	$(LIBFT_DIR)/$(INCLD_DIR)/
	$(MLX_DIR)/
endef
INCLD_FLAG 	:= ${addprefix -I , ${INCLUDES}}

define INCLD_FILES :=
	main.h
endef

### LIB ###
LIBFT			:= ${LIBFT_DIR}/libft.a
MLX 			:= ${MLX_DIR}/libmlx.a
LIB 			:= ${LIBFT} ${MLX} -lXext -lX11 -lm
LIBFT_OBJS_DIR	:= ${LIBFT_DIR}/objs



### SRCS ###
define SRC 	:=
	main.c \
	loop.c \
	parsing/check_file.c \
	parsing/check_file2.c \
	parsing/check_map.c \
	parsing/check_map2.c \
	parsing/load_color.c \
	parsing/load_textures.c \
	raycasting/raycasting.c \
	raycasting/raycasting2.c \
	raycasting/movement.c \
	raycasting/rotate.c \
	raycasting/position.c \
	utils.c \
	utils2.c \
	utils3.c
endef

SRC 		:= ${strip ${SRC}}
OBJS 		:= ${patsubst %.c,${OBJS_DIR}/%.o,${SRC}}
DEPS		:= ${patsubst %.c,${OBJS_DIR}/%.d,${SRC}}

### PROJECT ###
all: ${NAME}

${MLX}:
	@make -C ${MLX_DIR}

${NAME}: ${LIB} ${OBJS}
	@printf "${NEW}${PURPLE}[${NAME}] ${UGREEN}Compiling :${DEFAULT}${BWHITE} $@${DEFAULT}"
	@${CC} ${CFLAGS} ${OBJS} ${LIB} ${INCLD_FLAG} -o $@
	@printf "\n"

-include ${DEPS}
${OBJS_DIR}/%.o: ${SRC_DIR}/%.c
	@printf "${NEW}${PURPLE}[${NAME}] ${UGREEN}Compiling :${DEFAULT} $<"
	@mkdir -p ${dir $@}
	@${CC} ${DEP_FLAGS} ${CFLAGS} ${INCLD_FLAG} -c $< -o $@

clean:
	@printf "${PURPLE}[${NAME}] ${RED}Cleaning ${DEFAULT}${OBJS_DIR} files.\n"
	@${RM} ${OBJS_DIR} ${OBJS_BONUS_DIR}

fclean: clean
	@printf "${PURPLE}[${NAME}] ${RED}Cleaning ${DEFAULT}${NAME}.\n"
	@${RM} ${NAME}

re: fclean all

### LIBFT ###
${LIBFT}:
	@mkdir -p ${LIBFT_OBJS_DIR}
	@make -C ${LIBFT_DIR} OBJ_DIR=${LIBFT_OBJS_DIR} ${MAKE_FLAG}

lib: ${LIBFT}
	@mv ${LIBFT_DIR}/*.o ${LIBFT_OBJS_DIR}/ 2>/dev/null || true
	@mv ${LIBFT_DIR}/ft_gnl/*.o ${LIBFT_OBJS_DIR}/ 2>/dev/null || true
	@mv ${LIBFT_DIR}/ft_printf/*.o ${LIBFT_OBJS_DIR}/ 2>/dev/null || true

cleanlib:
	@make -C ${LIBFT_DIR} clean ${MAKE_FLAG}
	@rm -rf ${LIBFT_OBJS_DIR}
	@printf "${PURPLE}[${LIBFT_DIR}] ${RED}Cleaned object files.${DEFAULT}\n"

fcleanlib:
	@make -C ${LIBFT_DIR} fclean ${MAKE_FLAG}
	@rm -rf ${LIBFT_OBJS_DIR}
	@printf "${PURPLE}[${LIBFT_DIR}] ${RED}Library and object files cleaned.${DEFAULT}\n"

relib:
	@make -C ${LIBFT_DIR} re ${MAKE_FLAG}

### NORM ###
norm: ; @make -C ${LIBFT_DIR} norm ${MAKE_FLAG}
	@norminette ${SRC_DIR} ${INCLD_DIR}

watch:
	watch norminette ${SRC_DIR} ${INCLD_DIR}

### TEST ###
test: $(NAME)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=./$(NAME)

.PHONY: all clean fclean re cleanlib fcleanlib relib norm watch format run test

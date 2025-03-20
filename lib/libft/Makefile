### PROGRAM_NAME ###
NAME = libft.a

### UTILS ###
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SILENT_FLAG := --no-print-directory --silent

### COLORS ###
DEFAULT := \033[0m
PURPLE  := \033[0;35m
UGREEN  := \033[4;32m
BWHITE  := \033[1;37m
NEW     := \r\033[K

### DIRECTORIES ###
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcat.c ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strncmp.c \
	ft_strcmp.c ft_atoi.c ft_strchr.c ft_strrchr.c ft_strnstr.c \
	ft_memcmp.c ft_memchr.c ft_strdup.c ft_strndup.c ft_calloc.c \
	ft_split.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_striteri.c \
	ft_strmapi.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
	ft_lstsize.c ft_fsplit.c ft_ftab.c ft_strcut.c

GNL_SRC = ft_gnl/get_next_line.c ft_gnl/get_next_line_utils.c
PRT_SRC = ft_printf/conversion.c ft_printf/conversion2.c ft_printf/ft_printf.c

# Ensure OBJ_DIR is set to the correct path
OBJ_DIR = objs

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o) $(GNL_SRC:.c=.o) $(PRT_SRC:.c=.o))
INCLD_DIR = include/

### RULES ###
all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(NEW)$(PURPLE)[$@] $(UGREEN)Building:$(DEFAULT)$(BWHITE) $@$(DEFAULT)"
	@ar rcs $@ $(OBJS)
	@printf "\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(NEW)$(PURPLE)[$(NAME)] $(UGREEN)Building:$(DEFAULT) $<"
	@$(CC) $(CFLAGS) -I$(INCLD_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@mkdir -p $(OBJ_DIR) # Recreate the objs folder
	@printf "$(PURPLE)[$(NAME)] $(RED)Cleaned object files.$(DEFAULT)\n"

fclean:
	@$(RM) $(OBJS) $(NAME)
	@printf "$(PURPLE)[$(NAME)] $(RED)Cleaned library and object files.$(DEFAULT)\n"

re: fclean all

relib:
	@$(MAKE) fclean ${SILENT_FLAG}
	@$(MAKE) all ${SILENT_FLAG}
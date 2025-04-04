# =======================================
# Main Variables - Variables / Values
# =======================================

CC			=	cc
NAME		=	minishell
CCFLAGS ?=	-Wall -Werror -Wextra -MMD -MP
CPPFLAGS = -lreadline

# =======================================
# Main Directories - Paths
# =======================================

SRCS		=	minishell.c \
				parsing.c   \
				init.c      \

OBJS		= $(SRCS:.c=.o)
DEPS		= $(OBJS:.o=.d)

SRC_D		=	src/
OBJ_D		=	obj/
INC_D		=	-Iinclude \
					-Ilibs/libft/includes

# =======================================
# Objets Files
# =======================================

.PHONY: all
all: 
	$(MAKE) -C libs/libft
	$(MAKE) $(NAME)

OBJS	:= $(addprefix $(OBJ_D), $(OBJS))
SRCS	:= $(addprefix $(SRC_D), $(SRCS))

$(NAME):$(OBJS)
	$(CC) $(CCFLAGS) $(INC_D) $(CPPFLAGS) $(OBJS) -lm libs/libft/libft.a -o $@

$(OBJ_D)%.o: $(SRC_D)%.c | $(OBJ_D)
	$(CC) $(CCFLAGS) $(INC_D) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_D)
	$(MAKE) clean -C libs/libft

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	$(MAKE) fclean -C libs/libft

.PHONY: debug
debug:
	$(MAKE) CCFLAGS="-g3"

.PHONY: re
re:	fclean all

$(OBJ_D):
	mkdir -p $(OBJ_D)

-include $(DEPS)% 

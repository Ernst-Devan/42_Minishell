# =======================================
# Main Variables - Variables / Values
# =======================================

CC			=	cc
NAME		=	minishell
CCFLAGS ?=	-g3 -Wall -Werror -Wextra -MMD -MP
CPPFLAGS = -lreadline

# =======================================
# Main Directories - Paths
# =======================================

SRCS		=	minishell.c 	\
				parsing.c   	\
				init.c      	\
				exec.c 			\
				ms_cd.c 		\
				check.c			\
				env_manage.c 	\
				free.c			\
				lexer.c			\
				redirection.c	\
				env.c			\
				error.c			\
				export.c		\
				parser.c		\
				pipe.c			\
				utils.c			\
				quotes.c		\
				echo.c 			\
				pwd.c			\
				unset.c 		\
				exit.c 			\
				remove_cd.c     \
				pwd_manage.c 	\
				command_split.c \
				ctrl_c.c 		\
				expand.c		\
				prompt.c		\
				manage_in.c 	\
				manage_out.c 	\
				lexical_analyse.c \

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
	@if ! readelf --debug-dump=info obj/init.o | grep -q "Version"; then \
		$(MAKE) fclean; \
	fi
	bash -c "echo -en '\033c\033[3J'"
	$(MAKE) debug -C libs/libft;
	$(MAKE) CCFLAGS="-Wall -Wextra -MMD -MP -g3"
	bash -c "valgrind --leak-check=full --suppressions=valgrind_readline.supp ./minishell"
	
.PHONY: debuga 
debuga:
	@if ! readelf --debug-dump=info obj/init.o | grep -q "Version"; then \
		$(MAKE) fclean; \
		$(MAKE) debug -C libs/libft; \
	fi
	bash -c "echo -en '\033c\033[3J'"
	$(MAKE) CCFLAGS="-Wall -Wextra -MMD -MP -g3"
	bash -c "valgrind --leak-check=full --track-fds=yes ./minishell"

.PHONY: re
re:	fclean all

$(OBJ_D):
	mkdir -p $(OBJ_D)

-include $(DEPS)% 

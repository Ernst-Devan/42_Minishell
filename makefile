NAME := minishell

# --- SRC/DIR --- #

SRC_DIR := src/

BUILTINS_DIR := builtins/

BUILTINS_SRCS :=	echo.c \
					env.c	\
					exit.c	\
					export.c	\
					ms_cd.c 	\
					pwd_manage.c	\
					pwd.c 			\
					remove_cd_utils.c 	\
					remove_cd.c 		\
					unset.c 			\
					utils_export.c 		\
					utils_export2.c 		\

SRCS += $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRCS))

EXEC_DIR :=	exec/

EXEC_SRCS :=	exec.c	\
				pipe.c 	\
				pipe_utils.c \

SRCS += $(addprefix $(EXEC_DIR), $(EXEC_SRCS))

MANAGE_FILES_DIR := manage_files/

MANAGE_FILES_SRCS := manage_fd.c 			\
						manage_heredoc.c 	\
						manage_in.c 		\
						manage_out.c 		\

SRCS += $(addprefix $(MANAGE_FILES_DIR), $(MANAGE_FILES_SRCS))

PARSING_DIR  := parsing/

PARSING_SRCS := alloc_expand.c 	\
				check.c 		\
				env_manage.c 	\
				expand.c 		\
				init.c 			\
				lexer.c 		\
				lexical_analyse.c 	\
				parser.c 			\
				parsing.c 			\
				prompt.c 			\
				quotes.c 			\
				redirection.c 		\
				utils_lexical_analyse.c \
				expand_utils.c			\
				redirection_utils.c		\
				redirection_utils2.c	\

SRCS += $(addprefix $(PARSING_DIR), $(PARSING_SRCS))

TOOLS_DIR := tools/

TOOLS_SRCS := command_split.c \
				ctrl_c.c 		\
				debug.c 		\
				error.c 		\
				free.c 			\
				space.c 		\
				utils.c 		\

SRCS += $(addprefix $(TOOLS_DIR), $(TOOLS_SRCS))

SRCS += minishell.c

# --- LIBS TARGET --- #

LIBS_TARGET :=			\
	libs/libft/libft.a 	\

LIBS := $(patsubst lib%.a, %, $(notdir $(LIBS_TARGET)))

# --- INCLUDES --- #

INCLUDES := includes/

# --- OBJS/DEPS --- #

OBJS_DIR := .build/objs/

OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))


DEPS := $(OBJS:.o=.d)

# --- FLAGS --- #

CPPFLAGS += -MMD -MP $(addprefix -I,$(INCLUDES)) \
					 $(addprefix -I,$(addsuffix $(INCLUDES),$(dir $(LIBS_TARGET))))

CFLAGS += -g3 -Wall -Wextra -Werror

LFLAGS += 	$(addprefix -L,$(dir $(LIBS_TARGET))) \
			$(addprefix -l,$(LIBS)) \
			-lreadline

# --- COMPILATER --- #

CC = cc

# --- EXEC --- #

all : $(NAME)

$(NAME) : $(LIBS_TARGET) $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(LIBS_TARGET) : force
	$(MAKE) -C $(dir $@)

force:

.PHONY : clean fclean all re print-% debug force

clean:
	rm -rf .build
	$(MAKE) clean -C $(dir $(LIBS_TARGET))

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(dir $(LIBS_TARGET))

re:
	$(MAKE) fclean
	$(MAKE) all

debug: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind_readline.supp ./$(NAME)

print-%:
	@echo $(patsubst print-%,%,$@)=
	@echo $($(patsubst print-%,%,$@))

-include $(DEPS)

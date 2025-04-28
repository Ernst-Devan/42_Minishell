#========================================
# Main Variables - Variables / Values
# =======================================

CC			=	cc
CCFLAGS		?=	-Wall -Werror -Wextra
CPPFLAGS	=  $(INCLUDES_D)
NAME		=	libft.a

# =======================================
# Main Directories - Paths
# =======================================


OBJ_D		=	objs/
SRC_D		=	srcs/
BIN_D		=	bin/
INCLUDES_D	=	-Iincludes/

FT_IS_D		=	is/
FT_STR_D	=	str/
FT_MEM_D	=	memory/
FT_PUT_D	=	write/
FT_INT_D	=	int/
FT_TO_D		=	to/
FT_ALLOC_D	=	allocation/
FT_LST_D	=	chained_list/
FT_PRINTF_D	=	printf/
GNL_D 		= 	gnl/

# =======================================
# Source Files - Character Checks
# =======================================

FT_IS_SRC =						\
	ft_isalpha.c				\
	ft_isdigit.c				\
	ft_isalnum.c				\
	ft_isascii.c				\
	ft_isprint.c				\
	ft_isspace.c				\
	ft_islower.c				\
	ft_isupper.c				\

# =======================================
# Source Files - String Functions
# =======================================

FT_STR_SRC =					\
	ft_count_word.c			\
	ft_strlen.c					\
	ft_strchr.c					\
	ft_strrchr.c				\
	ft_strlcpy.c				\
	ft_strlcat.c				\
	ft_strncmp.c				\
	ft_strnstr.c				\
	ft_strdup.c					\
	ft_substr.c					\
	ft_strjoin.c				\
	ft_strtrim.c				\
	ft_split.c					\
	ft_strmapi.c				\
	ft_striteri.c				\
	ft_strtol.c					\
	ft_bzero.c

# =======================================
# Source Files - Memory Functions
# =======================================

FT_MEM_SRC =					\
	ft_memset.c					\
	ft_memcpy.c					\
	ft_memchr.c					\
	ft_memmove.c				\
	ft_memcmp.c

# =======================================
# Source Files - Display Functions
# =======================================

FT_PUT_SRC =					\
	ft_putchar_fd.c				\
	ft_putstr_fd.c 				\
	ft_putendl_fd.c				\
	ft_putnbr_fd.c				\
	ft_putnbr_base.c			\
	ft_putunbr_base.c

# =======================================
# Source Files - Int Functions
# =======================================

FT_INT_SRC =					\
	ft_intlen.c					\
	ft_intlen_base.c		\
	ft_uintlen_base.c		\
	ft_abs.c
# =======================================
# Source Files - Convert Function
# =======================================

FT_TO_SRC =						\
		ft_toupper.c			\
		ft_tolower.c			\
		ft_atoi.c				\
		ft_itoa.c

# =======================================
# Source Files - Malloc Functions
# =======================================

FT_ALLOC_SRC =					\
	ft_calloc.c

# =======================================
# Source Files - List Functions
# =======================================

FT_LST_SRC =					\
	ft_lstnew_bonus.c			\
	ft_lstadd_front_bonus.c 	\
	ft_lstsize_bonus.c 			\
	ft_lstlast_bonus.c 			\
	ft_lstadd_back_bonus.c 		\


# =======================================
# Source Files - List Functions
# =======================================

FT_PRINTF_SRC =					\
	ft_printf.c					\
	utils_printf.c

# =======================================
# Source Files - GetNextLine
# =======================================

GNL_SRC		 =					\
	get_next_line.c				\
	get_next_line_utils.c

# =======================================
# Adding Paths to the Source Files
# =======================================

FT_IS_SRC		:=	$(addprefix $(SRC_D)$(FT_IS_D),		$(FT_IS_SRC))
FT_STR_SRC		:=	$(addprefix $(SRC_D)$(FT_STR_D),	$(FT_STR_SRC))
FT_MEM_SRC		:=	$(addprefix $(SRC_D)$(FT_MEM_D),	$(FT_MEM_SRC))
FT_PUT_SRC		:=	$(addprefix $(SRC_D)$(FT_PUT_D),	$(FT_PUT_SRC))
FT_INT_SRC		:=	$(addprefix $(SRC_D)$(FT_INT_D),	$(FT_INT_SRC))
FT_TO_SRC		:=	$(addprefix $(SRC_D)$(FT_TO_D),		$(FT_TO_SRC))
FT_ALLOC_SRC	:=	$(addprefix $(SRC_D)$(FT_ALLOC_D),	$(FT_ALLOC_SRC))
FT_LST_SRC		:=	$(addprefix $(SRC_D)$(FT_LST_D),	$(FT_LST_SRC))
FT_PRINTF_SRC	:=	$(addprefix $(SRC_D)$(FT_PRINTF_D),	$(FT_PRINTF_SRC))
GNL_SRC			:=	$(addprefix $(SRC_D)$(GNL_D),		$(GNL_SRC))

# =======================================
# Combine All Sources Files
# =======================================

SRCS = $(FT_IS_SRC) $(FT_STR_SRC) $(FT_MEM_SRC) $(FT_PUT_SRC) $(FT_INT_SRC) $(FT_TO_SRC) $(FT_ALLOC_SRC) $(FT_LST_SRC) $(FT_PRINTF_SRC) $(GNL_SRC)

# =======================================
# Objets Files
# =======================================

OBJS = $(patsubst $(SRC_D)%.c, $(OBJ_D)%.o ,$(SRCS))

# =======================================
# Commands
# =======================================

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_D)%.o:$(SRC_D)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BIN_D):
	mkdir -p $(BIN_D)

.PHONY: debug
debug:
	$(MAKE) CFLAGS="-g3"

.PHONY: clean
clean: 
	rm -rf $(OBJ_D)
	rm -rf $(BIN_D)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

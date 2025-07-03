NAME = minishell
FLAGS =  -Wall -Wextra -Werror #-fsanitize=address
SFLAGS = -lreadline
COMP = cc
HEADRES = main/minishell.h Libft/libft.h

SRCS = 	main/minishell.c\
		utils/find_paths.c\
		env/get_env.c\
		env/env_tools.c\
		excute/built_in/do_cd.c\
		excute/built_in/do_echo.c\
		parsing/parssing.c\
		excute/built_in/do_unset.c\
		excute/built_in/do_env.c\
		excute/built_in/do_pwd.c\
		excute/built_in/do_export.c\
		excute/built_in/utils.c\
		utils/ft_malloc.c\
		excute/built_in/do_exit.c\
		excute/redirections/redr.c\
		excute/redirections/pipe_tools.c\
		excute/redirections/pipe_tools2.c\
		excute/excute.c\
		excute/excute_tools.c\
		excute/shlvl.c\
		excute/redirections/heredoc.c\
		excute/redirections/pipe.c\
		excute/signals.c\
		parsing/invalid_syntax.c\
		parsing/parss_input.c\
		parsing/parssing_tools.c\
		parsing/split_pipe.c\
		parsing/valid_syntax.c\
		parsing/split.c\
		parsing/expand.c\
		parsing/add_spaces.c\
		parsing/check_syntax.c\
		parsing/check_expand_quotes.c\
		parsing/init.c

SRC_LIBFT	= 	LIBFT/ft_isalpha.c\
		LIBFT/ft_isdigit.c\
		LIBFT/ft_isalnum.c\
		LIBFT/ft_isascii.c\
		LIBFT/ft_isprint.c\
		LIBFT/ft_strlen.c\
		LIBFT/ft_memset.c\
		LIBFT/ft_bzero.c\
		LIBFT/ft_memcpy.c\
		LIBFT/ft_memmove.c\
		LIBFT/ft_strlcpy.c\
		LIBFT/ft_strlcat.c\
		LIBFT/ft_toupper.c\
		LIBFT/ft_tolower.c\
		LIBFT/ft_strchr.c\
		LIBFT/ft_strrchr.c\
		LIBFT/ft_strncmp.c\
		LIBFT/ft_strcmp.c\
		LIBFT/ft_memchr.c\
		LIBFT/ft_memcmp.c\
		LIBFT/ft_strnstr.c\
		LIBFT/ft_atoi.c\
		LIBFT/ft_calloc.c\
		LIBFT/ft_strdup.c\
		LIBFT/ft_substr.c\
		LIBFT/ft_strjoin.c\
		LIBFT/ft_strtrim.c\
		LIBFT/ft_split.c\
		LIBFT/ft_itoa.c\
		LIBFT/ft_striteri.c\
		LIBFT/ft_putchar_fd.c\
		LIBFT/ft_putstr_fd.c\
		LIBFT/ft_putendl_fd.c\
		LIBFT/ft_putnbr_fd.c\
		LIBFT/ft_lstnew_bonus.c\
		LIBFT/ft_lstadd_front_bonus.c\
		LIBFT/ft_lstsize_bonus.c\
		LIBFT/ft_lstlast_bonus.c\
		LIBFT/ft_lstadd_back_bonus.c\
		LIBFT/ft_lstdelone_bonus.c\
		LIBFT/ft_lstclear_bonus.c\
		LIBFT/ft_lstiter_bonus.c

OBGS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBGS) $(SRC_LIBFT)
	make -C Libft
	$(COMP) $(FLAGS) $(OBGS) Libft/libft.a $(SFLAGS) -o $@

%.o: %.c $(HEADRES)
	$(COMP) $(FLAGS) -c $< -o $@

clean:
	make clean -C Libft
	rm -rf $(OBGS)

fclean: clean
	make fclean -C Libft
	rm -rf $(NAME)

re: fclean all

.PHONY: clean
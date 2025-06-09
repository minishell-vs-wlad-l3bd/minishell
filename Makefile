NAME = minishell
FLAGS =  -Wall -Wextra -Werror -fsanitize=address
SFLAGS = -lreadline
COMP = cc
HEADRES = main/minishell.h

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
		utils/ft_malloc.c\
		excute/built_in/do_exit.c\
		excute/redirections/redr.c\
		excute/excute.c\
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
		parsing/add_spaces.c 

OBGS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	@make -C Libft
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
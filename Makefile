NAME = minishell
# FLAGS = -Wall -Wextra -Werror 
SFLAGS = -lreadline
COMP = cc
HEADRES = minishell.h Libft/libft.h
SRCS = minishell.c find_paths.c env/get_env.c env/lst_tools.c built_in/do_cd.c built_in/do_echo.c

OBGS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	make re -C Libft
	$(COMP) $(FLAGS)  $(OBGS) Libft/libft.a $(SFLAGS) -o $@

%.o: %.c $(HEADRES)
	$(COMP) $(FLAGS) -c -o $@ $<

clean:
	make clean -C Libft
	rm -rf $(OBGS)

fclean: clean
	make fclean -C Libft
	rm -rf $(NAME)

re: fclean all

.PHONY: clean
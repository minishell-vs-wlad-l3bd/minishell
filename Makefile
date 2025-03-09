NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
SFLAGS = -lreadline
COMP = cc
HEADRES = minishell.h Libft/libft.h
SRCS = minishell.c find_paths.c

OBGS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	make re -C Libft
	$(COMP) $(CFLAGS) $(SFLAGS) $(OBGS) Libft/libft.a -o $@

%.o: %.c $(HEADRES)
	$(COMP) $(CFLAGS) -c -o $@ $<

clean:
	make clean -C Libft
	rm -rf $(OBGS)

fclean: clean
	make fclean -C Libft
	rm -rf $(NAME)

re: fclean all

.PHONY: clean
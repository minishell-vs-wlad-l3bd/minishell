NAME = minishell
CFLAGS =  -lreadline
COMP = cc
HEADRES = minishell.h Libft/libft.h
SRCS = minishell.c find_paths.c

OBGS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	make re -C Libft
	$(COMP) $(CFLAGS)  $(OBGS) Libft/libft.a -o $@

%.o: %.c $(HEADRES)
	$(COMP) $(CFLAGS) -c -o $@ $<

clean:
	make clean -C Libft
	rm -rf $(OBGS)

fclean: clean
	make fclean -C Libft
	rm -rf $(OBGS)

re: fclean all

.PHONY: clean
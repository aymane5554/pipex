CC = cc
CFLAFS = -Wall -Wextra -Werror
SRCS = main.c init.c
SHSRCS = utils.c
SHOBJS = $(SHSRCS:%.c=%.o)
BSRCS= bonus/main_bonus.c bonus/init_bonus.c bonus/get_input.c bonus/remove_bonus.c
OBJS = $(SRCS:%.c=%.o)
BOBJS= $(BSRCS:bonus/%.c=bonus/%.o)

NAME = pipex

all:$(NAME)

objects:
	@cd libft && make objects && cd ..

bonus: pipex_bonus

bonus/%.o : bonus/%.c bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -I libft/ -o $@

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -c $< -I libft/ -o $@

pipex_bonus: $(BOBJS) $(SHOBJS) libft/libft.a objects
	$(CC) $(CFLAFS) $(BOBJS) $(SHOBJS) -I . -I libft/ -L libft/ -lft -o pipex_bonus

$(NAME) : $(OBJS) $(SHOBJS) libft/libft.a
	$(CC) $(CFLAFS) $(OBJS) $(SHOBJS) -I libft/ -L libft/ -lft -o $(NAME)

libft/libft.a: libft/libft.h libft/get_next_line.h objects
	@echo making libft...
	@cd libft && make all bonus && cd ..

clean:
	rm -f $(OBJS) $(BOBJS) $(SHOBJS) && cd libft && make clean && cd ..

fclean: clean
	rm -f pipex pipex_bonus && cd libft && rm -f libft.a && cd ..

re: fclean all

.PHONY: clean
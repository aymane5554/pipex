CC = cc
CFLAFS = -Wall -Wextra -Werror
SRCS = main.c init.c
SHSRCS = utils.c
SHOBJS = $(SHSRCS:%.c=%.o)
BSRCS= bonus/main_bonus.c bonus/init_bonus.c bonus/get_input.c bonus/remove_bonus.c
OBJS = $(SRCS:%.c=%.o)
BOBJS= $(BSRCS:bonus/%.c=bonus/%.o)
LIBFT_OBJS = libft/ft_atoi.o libft/ft_bzero.o libft/ft_calloc.o libft/ft_isalnum.o libft/ft_isalpha.o \
            libft/ft_isascii.o libft/ft_isdigit.o libft/ft_isprint.o libft/ft_itoa.o libft/ft_memchr.o \
            libft/ft_memcmp.o libft/ft_memcpy.o libft/ft_memmove.o libft/ft_memset.o libft/ft_putchar_fd.o \
            libft/ft_putendl_fd.o libft/ft_putnbr_fd.o libft/ft_putstr_fd.o libft/ft_split.o \
            libft/ft_strchr.o libft/ft_strdup.o libft/ft_striteri.o libft/ft_strjoin.o libft/ft_strlcat.o \
            libft/ft_strlcpy.o libft/ft_strlen.o libft/ft_strmapi.o libft/ft_strncmp.o libft/ft_strnstr.o \
            libft/ft_strrchr.o libft/ft_strtrim.o libft/ft_substr.o libft/ft_tolower.o libft/ft_toupper.o \
			libft/get_next_line.o libft/get_next_line_utils.o libft/ft_lstnew_bonus.o \
			libft/ft_lstsize_bonus.o libft/ft_lstlast_bonus.o libft/ft_lstadd_front_bonus.o \
			libft/ft_lstadd_back_bonus.o libft/ft_lstdelone_bonus.o libft/ft_lstclear_bonus.o \
			libft/ft_lstiter_bonus.o libft/ft_lstmap_bonus.o

NAME = pipex

all:$(NAME)

bonus: pipex_bonus

bonus/%.o : bonus/%.c bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -I libft/ -o $@

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -c $< -I libft/ -o $@

pipex_bonus: $(BOBJS) $(SHOBJS) libft/libft.a
	$(CC) $(CFLAFS) $(BOBJS) $(SHOBJS) -I . -I libft/ -L libft/ -lft -o pipex_bonus

$(NAME) : $(OBJS) $(SHOBJS) libft/libft.a
	$(CC) $(CFLAFS) $(OBJS) $(SHOBJS) -I libft/ -L libft/ -lft -o $(NAME)

libft/libft.a: libft/libft.h libft/get_next_line.h $(LIBFT_OBJS)
	cd libft && make all bonus && cd ..

clean:
	rm -f $(OBJS) $(BOBJS) $(SHOBJS) && cd libft && make clean && cd ..

fclean: clean
	rm -f pipex pipex_bonus && cd libft && rm -f libft.a && cd ..

re: fclean all

.PHONY: clean
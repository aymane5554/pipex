CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c init.c
SHSRCS = utils.c
SHOBJS = $(SHSRCS:%.c=%.o)
BSRCS= bonus/main_bonus.c bonus/init_bonus.c bonus/get_input.c bonus/remove_bonus.c
OBJS = $(SRCS:%.c=%.o)
BOBJS= $(BSRCS:bonus/%.c=bonus/%.o)
LIBFT_SRCS = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c \
            libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c \
            libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c \
            libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c \
            libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c \
            libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c \
            libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c \
			libft/ft_lstnew_bonus.c \
			libft/ft_lstsize_bonus.c libft/ft_lstlast_bonus.c libft/ft_lstadd_front_bonus.c \
			libft/ft_lstadd_back_bonus.c libft/ft_lstdelone_bonus.c libft/ft_lstclear_bonus.c \
			libft/ft_lstiter_bonus.c libft/ft_lstmap_bonus.c
LIBFT_OBJS= $(LIBFT_SRCS:libft/%.c=libft/%.o)
GNL = get_next_line.c get_next_line_utils.c
GNLOBJ = $(GNL:get_next%.c=get_next%.o)
NAME = pipex

all:$(NAME)

bonus: pipex_bonus

bonus/%.o : bonus/%.c bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -I libft/ -o $@

get_next%.o : get_next%.c libft/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

libft/%.o : libft/%.c libft/libft.h
	$(CC) $(CFLAGS) -c $< -I libft/ -o $@

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -c $< -I libft/ -o $@


pipex_bonus: $(BOBJS) $(SHOBJS) libft/libft.a
	$(CC) $(CFLAGS) $(BOBJS) $(SHOBJS) -I . -I libft/ -L libft/ -lft -o pipex_bonus

$(NAME) : $(OBJS) $(SHOBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(SHOBJS) -I libft/ -L libft/ -lft -o $(NAME)

libft/libft.a: libft/libft.h libft/get_next_line.h $(LIBFT_OBJS)
	cd libft && make all bonus && cd ..

clean:
	rm -f $(OBJS) $(BOBJS) $(SHOBJS) && cd libft && make clean && cd ..

fclean: clean
	rm -f pipex pipex_bonus && cd libft && rm -f libft.a && cd ..

re: fclean all

.PHONY: clean
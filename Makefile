NAME = philo
SRC = philo.c \
main.c \
utils. 
HEADERFILES = -I philo.h
OBJFILES = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g3
CC = cc
# 
$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(NAME)

all: $(NAME)

%.o: %.c $(HEADERFILES)
	$(CC) -c $(CFLAGS) -o $@ $< 

clean:
	rm -f $(OBJFILES)

fclean:
	rm -f $(NAME) $(OBJFILES)

re: fclean all
	
.PHONY: clean fclean all re
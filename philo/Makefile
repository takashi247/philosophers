NAME		:= philo

CC			:= gcc

CFLAGS		:= -Wall -Wextra -Werror

SRCSDIR		:= srcs/

OBJSDIR		:= objs/

SRCS		:= $(shell find $(SRCSDIR) -name '*.c' | xargs basename -a)

OBJS		:= $(addprefix $(OBJSDIR), $(SRCS:.c=.o))

SRCS		:= $(addprefix $(SRCSDIR), $(SRCS))

SRCSBONUS	:= $(addprefix $(SRCSDIR), $(SRCSBONUS))

INCLUDE		:= -I./include

# LIBRARY		:= -L$(LIBDIR) -lft

RM			:= rm -rf

DEBUG		:= -fsanitize=address -g

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBPATH)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	@if [ ! -d $(OBJSDIR) ]; then mkdir $(OBJSDIR); fi
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJSDIR)
	$(RM) -rf *.dSYM

fclean:		clean
	$(RM) $(NAME) $(CHECKER)

re:			fclean all

debug:		CFLAGS += $(DEBUG)
debug:		re

.PHONY:		all clean fclean re debug
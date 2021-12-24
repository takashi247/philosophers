NAME		:= philo

CC			:= gcc

CFLAGS		:= -Wall -Wextra -Werror

SRCSDIR		:= srcs/

OBJSDIR		:= objs/

SRCS		:= $(shell find $(SRCSDIR) -name '*.c' | xargs basename -a)

OBJS		:= $(addprefix $(OBJSDIR), $(SRCS:.c=.o))

SRCS		:= $(addprefix $(SRCSDIR), $(SRCS))

SRCSBONUS	:= $(addprefix $(SRCSDIR), $(SRCSBONUS))

VPATH		:= $(SRCSDIR)

INCLUDE		:= -I./include

RM			:= rm -rf

DEBUG		:= -fsanitize=thread -g

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBPATH)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

$(OBJSDIR)%.o: %.c
	@if [ ! -d $(OBJSDIR) ]; then mkdir $(OBJSDIR); fi
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJSDIR)
	$(RM) -rf *.dSYM

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

debug:		CFLAGS += $(DEBUG)
debug:		re

.PHONY:		all clean fclean re debug
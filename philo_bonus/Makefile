NAME		:= philo_bonus

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

DEBUG		:= -g #-fsanitize=thread

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBPATH)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

$(OBJSDIR)%.o: %.c
	@if [ ! -d $(OBJSDIR) ]; then mkdir $(OBJSDIR); fi
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

bonus:		$(NAME)

clean:
	$(RM) $(OBJSDIR)
	$(RM) *.dSYM

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

test:		$(NAME)
	@bash ./test/error_test.sh

debug:		CFLAGS += $(DEBUG)
debug:		re

.PHONY:		all clean fclean re debug bonus
NAME		=	philo

INCLUDES	=	includes/
SRCS_FOLDER	=	srcs/
OBJS_FOLDER	=	.objs/

SRCS_FILES	=	main.c error.c ft_strtoi.c parsing.c \
				philo_struct.c philo_life.c philo_init.c philo_forks.c \
				philo_monitor.c \
				print.c check.c

OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))

DEPS		=	Makefile
STATIC_LINK	=	-lpthread

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)

.PHONY		=	all clean fclean test re

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n-----COMPILING $(NAME)-------\n"
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LINK) -o $(NAME)
	@echo "Executable has been successfully created."

$(OBJS_FOLDER)%.o: $(SRCS_FOLDER)%.c $(INCLUDES)$(NAME).h $(DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "\n-------------CLEAN--------------\n"
	rm -rf $(OBJS_FOLDER)
	@echo "object files have been removed."

fclean: clean
	@echo "\n-------------FORCE CLEAN--------------\n"
	rm -rf $(NAME)
	@echo "$(NAME) and object files have been removed."

re: fclean all

NAME		=	philo
BONUS_NAME	=	philo_bonus

INCLUDES	=	includes/
SRCS_FOLDER	=	srcs/
SRCS_BONUS_FOLDER	=	srcs_bonus/
OBJS_FOLDER	=	.objs/
OBJS_BONUS_FOLDER	=	.objs_bonus/

SRCS_FILES	=	main.c error.c ft_strtoi.c parsing.c \
				philo_struct.c philo_life.c philo_init.c philo_forks.c \
				philo_monitor.c \
				print.c check.c

SRCS_BONUS_FILES	=	main.c error.c ft_strtoi.c ft_itoa.c ft_strjoin.c parsing.c \
						philo_end_monitor.c philo_monitor.c philo_init.c \
						philo_life.c \
						print.c time.c

OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))
SRCS_BONUS	=	$(addprefix $(SRCS_BONUS_FOLDER),$(SRCS_BONUS_FILES))
OBJS_BONUS	=	$(addprefix $(OBJS_BONUS_FOLDER),$(SRCS_BONUS_FILES:.c=.o))

DEPS		=	Makefile
STATIC_LINK	=	-lpthread

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)

.PHONY		=	all clean fclean test re bonus

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n-----COMPILING $(NAME)-------\n"
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LINK) -o $(NAME)
	@echo "Executable has been successfully created."

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_BONUS)
	@echo "\n-----COMPILING $(BONUS_NAME)-------\n"
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(STATIC_LINK) -o $(BONUS_NAME)
	@echo "Executable has been successfully created."

$(OBJS_FOLDER)%.o: $(SRCS_FOLDER)%.c $(INCLUDES)$(NAME).h $(DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJS_BONUS_FOLDER)%.o: $(SRCS_BONUS_FOLDER)%.c $(INCLUDES)$(BONUS_NAME).h $(DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "\n-------------CLEAN--------------\n"
	rm -rf $(OBJS_FOLDER)
	rm -rf $(OBJS_BONUS_FOLDER)
	@echo "object files have been removed."

fclean: clean
	@echo "\n-------------FORCE CLEAN--------------\n"
	rm -rf $(NAME) $(BONUS_NAME)
	@echo "$(NAME) and object files have been removed."

re: fclean all

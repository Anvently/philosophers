NAME		=	philo
BONUS_NAME	=

INCLUDES	=	includes/
SRCS_FOLDER	=	sources/
OBJS_FOLDER	=	objects/

SRCS_FILES	=	main.c

OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))

DEPS		=	$(INCLUDES)libft.h
STATIC_LINK	=

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)

.PHONY		=	all clean fclean test re bonus

all: $(NAME)

$(NAME): $(DEPS) $(OBJS)
	@echo "\n-----COMPILING $(NAME)-------\n"
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LINK) -o $(NAME)
	@echo "Executable has been successfully created."

bonus: $(BONUS_NAME)

$(OBJS_FOLDER)%.o: $(SRCS_FOLDER)%.c Makefile $(INCLUDES)$(NAME).h $(DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "\n-------------CLEAN--------------\n"
	make clean -C libft/
	make clean -C libmlx/
	rm -rf $(OBJS_FOLDER)
	@echo "object files have been removed."

fclean: clean
	@echo "\n-------------FORCE CLEAN--------------\n"
	make fclean -C libft/
	rm -rf $(NAME) $(BONUS_NAME)
	@echo "$(NAME) and object files have been removed."

re: fclean all

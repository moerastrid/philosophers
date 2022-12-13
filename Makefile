# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.42.fr>                +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/07 16:12:00 by ageels        #+#    #+#                  #
#    Updated: 2022/12/02 15:59:20 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread
SRC = src/main.c\
	src/activity.c\
	src/convert.c\
	src/monitor.c\
	src/philosophy.c\
	src/phorks.c\
	src/time.c\
	src/utils.c\

GREEN = \x1b[32m
RESET = \033[0m

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

all : $(NAME)

obj_folder : 
	@mkdir -pv obj

$(NAME) : obj_folder $(OBJ)
	@clang $(CFLAGS) $(LFLAGS) $(OBJ) -o $@
	@echo "$(GREEN)philosophy is alive$(RESET)"

obj/%.o : src/%.c
	@clang $(CFLAGS) -o $@ -c $^

clean:
	@test -e obj && rm -fr obj && echo "$(GREEN)philosophy is dead$(RESET)" || echo "$(GREEN)philo: no obj to clean$(RESET)"

fclean: clean
	@test -e $(NAME) && rm $(NAME) || echo "$(GREEN)philo: no executable to clean$(RESET)"

re: fclean all

.PHONY: all clean fclean re
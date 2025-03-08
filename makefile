# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmassol <cmassol@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 03:52:33 by cmassol           #+#    #+#              #
#    Updated: 2025/03/08 01:23:58 by cmassol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = arphilo

HEADERS = philosophers.h

SOURCES = main.c time.c printer.c factory.c init.c engine.c pistons.c \
			firewatch.c utils.c utils2.c utils3_pmtx.c utils4_pmtx.c \
			utils5_tmtx.c utils6_tmtx.c

OBJECTS = $(addprefix $(OBJDIR)/,$(SOURCES:.c=.o))

OBJDIR = obj

CC = cc

FLAGS = -Wall -Wextra -Werror -pthread -g3

RM = rm -f

AR = ar rcs

PROGRAM = philo

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m


all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

deldir:
	$(RM) -r $(OBJDIR)

$(NAME): $(OBJECTS)
	@echo "              $(YELLOW) **** >>>>> Compiling: $(INFO) <<<<< **** $(DEF_COLOR)"
	$(CC) $(FLAGS) $(OBJECTS) -o $(PROGRAM)
	@echo ""
	@echo ""
	@echo "$(GREEN)          () () $(DEF_COLOR)"
	@echo "$(GREEN)          (>.<) $(DEF_COLOR)"
	@echo "$(GREEN)          ( . ) $(DEF_COLOR)"
	@echo "$(GREEN)           n_n  $(DEF_COLOR)"
	@echo "$(MAGENTA)>>>>> $(INFO) compiled!$(DEF_COLOR)"

$(OBJDIR)/%.o: %.c $(HEADERS)
	@echo "$(MAGENTA)CREATE OBJECTS FOR : $(DEF_COLOR)"
	$(CC) $(FLAGS) -c -o $@ $<
	
clean: deldir
	@echo "$(MAGENTA)CLEAN OBJECTS FOR :  $(OBJECTS) ! $(DEF_COLOR)"
	$(RM) $(OBJECTS) $(NAME)
	
fclean: clean
	@echo "$(MAGENTA)FCLEAN NAME FOR :  $(OBJECTS) ! $(DEF_COLOR)"
	$(RM) $(PROGRAM)
	
re: fclean all

.PHONY: all clean fclean re
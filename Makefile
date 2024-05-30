# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 11:24:23 by aconvent          #+#    #+#              #
#    Updated: 2024/05/30 14:25:39 by aconvent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######## Colours ########

RST = "\033[0m"
RED = "\033[31m"
GRN = "\033[32m"
YEL = "\033[33m"
BLU = "\033[34m"
MAG = "\033[35m"
CYN = "\033[36m"
WHT = "\033[37m"

######## Typographicals ########

BLD = "\033[1m"
FNT = "\033[2m"
ITA = "\033[3m"
UNL = "\033[4m"

######## Static lib Name ########

NAME = minishell

######## Directories ########

SRC_DIR = ./

FILES = \
			main \
			src/mini_hell \
			src/utils/ft_split \
			src/utils/utils\
			src/error \
			src/commands/echo \
			src/commands/pwd \
			src/commands/cd \
			src/commands/export \
			src/commands/unset \
			src/commands/env \
			src/commands/exit \
			src/parsing/parsing_utils

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(O_DIR), $(addsuffix .o, $(FILES)))

######## Compiler and flags ########

CC := cc #-fsanitize=address
CFLAGS =  #-Wall -Wextra -Werror 
######## first rule called by make ########

all : $(NAME)

######## creating the executable ########
$(NAME): $(OBJS) 
	@echo $(RED)Start compiling $(YEL)$(NAME) $(RST)
	@$(CC) $(CFLAGS) $(SRCS) -lreadline -o $(NAME)
	@echo $(GRN)Completed $(RST)

######## create the object dir if it doesn't exist ######## 

clean : 
	@echo $(RED)removing the object files $(MAG)$(OBJ_DIR)
	@rm -f $(OBJS)
	@echo $(GRN)completed $(RST)

######## same clean + removing the libprintf.h ######## 

fclean : clean 
	@echo $(RED)removing executable$(BLU) $(NAME)
	@rm $(NAME)
	@echo $(GRN)completed $(RST)
	
re : fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 11:24:23 by aconvent          #+#    #+#              #
#    Updated: 2024/04/25 11:24:29 by aconvent         ###   ########.fr        #
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

NAME = phonebook

######## Directories ########

SRC_DIR := ./src
OBJ_DIR = ./obj

######## Sources in each subdirectories ########

SRC_SUBDIRS := $(wildcard $(SRC_DIR)/*/)
SRCS_SUBDIR_FILES := $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)*.cpp))

######## Sources in the main directorie ########

SRCS_MAIN_DIR_FILES := $(wildcard $(SRC_DIR)/*.cpp)


######## All sources joined together ########

SRCS := $(SRCS_SUBDIR_FILES) $(SRCS_MAIN_DIR_FILES)
		
######## objects : make sure that every %.c files have their corresponding .o files ######## 
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

######## Compiler and flags ########

CPP := c++ 
CFLAGS = -Wall -Wextra -Werror -std=c++11 -I ./include

######## first rule called by make ########

all : $(NAME)

######## creating the executable ########
$(NAME): $(OBJS) 
	@echo $(RED)Start compiling $(YEL)$(NAME) $(RST)
	@$(CPP) $(OBJS) -o $(NAME)
	@echo $(GRN)Completed $(RST)

######## creating the objects files based on the c files and make sure the OBJ dir exist before creating them########
$(OBJ_DIR)/%.o: ./src/%.cpp 
	@mkdir -p $(dir $@)
	@echo $(RED)Compiling $(CYN) $< $(RST)
	@$(CPP) $(CFLAGS) -c $< -o $@
	@echo $(GRN)Completed $(RST)



######## create the object dir if it doesn't exist ######## 



clean : 
	@echo $(RED)removing the dir $(MAG)$(OBJ_DIR)
	@rm -rf  $(OBJ_DIR)
	@echo $(GRN)completed $(RST)

######## same clean + removing the libprintf.h ######## 

fclean : clean 
	@echo $(RED)removing executable$(BLU) $(NAME)
	@rm $(NAME)
	@echo $(GRN)completed $(RST)
	
re : fclean all

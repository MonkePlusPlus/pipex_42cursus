# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 14:32:26 by ptheo             #+#    #+#              #
#    Updated: 2024/08/28 15:36:49 by ptheo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

SRC		= ./src/

# FILE
FILE	= main_bonus.c
FILE	+= pipex_bonus.c
FILE	+= ft_split_add_bonus.c
FILE	+= pipex_utils_bonus.c
FILE	+= here_doc_bonus.c
# END OF FILE
SRC_FILE	= $(addprefix $(SRC), $(FILE))

OBJ			:= $(SRC_FILE:.c=.o)
INCLUDES	:= ./includes/

PATH_LIBFT	:= ./libft/
LIBFT		:= $(PATH_LIB)libft.a

CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -g3
LIB_FLAG	:= -L$(PATH_LIBFT) -lft

RM		:= rm -f
MAKE	:= make

all : $(NAME) $(PATH_LIBFT)

$(NAME) : $(OBJ) $(LIBFT)
		@echo "compilation of pipex file :"
		$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAG) -o $(NAME) -I$(INCLUDES)

$(LIBFT) : 
	@echo "compilate libft :"
	@$(MAKE) -C $(PATH_LIBFT) all

clean :
	@echo "clean libft :"
	@$(MAKE) -C $(PATH_LIBFT) clean
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean :
	@echo "fclean libft : "
	@$(MAKE) -C $(PATH_LIBFT) fclean
	$(RM) $(NAME) $(OBJ) $(OBJ_BONUS)

re : fclean all

.PHONY: all clean fclean bonus re
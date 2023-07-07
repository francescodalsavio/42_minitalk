# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frdal-sa <frdal-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/29 19:43:53 by francescoda       #+#    #+#              #
#    Updated: 2023/07/07 15:49:58 by frdal-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=
CLIENT	=	client
SERVER	=	server

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft


SRC_C	=	client.c utils/ft_putstr_color_fd.c utils/ft_straddc.c utils/ft_str_isnumeric.c utils/send_null_signal.c
SRC_S	=	server.c utils/ft_putstr_color_fd.c utils/ft_straddc.c
INC		=	-I. -I$(LIBFT_DIR)

CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(LIBFT)
	@ $(CC) $(D_FLAG) $(CFLAG) $(SRC_S) $(LIBFT) $(INC) -o $(SERVER)
	@printf "$(_SUCCESS) server ready.\n"

$(CLIENT): $(LIBFT)
	@ $(CC) $(D_FLAG) $(CFLAG) $(SRC_C) $(LIBFT) $(INC) -o $(CLIENT)
	@printf "$(_SUCCESS) client ready.\n"


$(LIBFT):
	@ $(MAKE) DEBUG=$(DEBUG) -C ./libft

clean:
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"

fclean:
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"

re: fclean all

mandatory:	$(CLIENT) $(SERVER)
bonus:		mandatory

m : mandatory
b : bonus

.PHONY: all clean fclean re mandatory m bonus b

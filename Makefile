# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 02:44:37 by abel-hid          #+#    #+#              #
#    Updated: 2023/11/22 16:31:46 by heddahbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

SRCS =	main.c\
		get_next_line.c\
		get_next_line_utils.c\
		split.c\

OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) MLX42/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -o $(NAME) 
%.o: %.c cub3D.h
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
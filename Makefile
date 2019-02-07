# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/05 12:24:50 by mtaquet      #+#   ##    ##    #+#        #
#    Updated: 2019/01/31 15:36:07 by mtaquet     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = $(addprefix vm_files/players/,mtaquet.filler)
LIBDIR = libft/
VISUDIR = visualisateur/
GENDIR = map_generator/
SRCDIR = srcs/
INCDIR = includes/
LIBFILES = libft.a
SRCFILES = main.c\
		   input.c\
		   check.c\
		   resol.c\
		   utils.c\

INCFILES = filler.h
LIB = $(addprefix $(LIBDIR),$(LIBFILES))
SRC = $(addprefix $(SRCDIR),$(SRCFILES))
INC = $(addprefix $(INCDIR),$(INCFILES)) libft/includes/libft.h
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra -I includes -I libft/includes

all: $(NAME) visu gen

%.o: %.c $(INC)
	gcc -c -o $@ $< $(FLAG)

$(LIB): $(LIBDIR)
	@make -C $(LIBDIR)

visu: $(VISUDIR)
	@make -C $(VISUDIR)

gen: $(GENDIR)
	@make -C $(GENDIR)

$(NAME): $(LIB) $(OBJ) $(INC)
	gcc -o $@ $(OBJ) $(FLAG) $(LIB)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBDIR)
	@make clean -C $(VISUDIR)
	@make clean -C $(GENDIR)


fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)
	@make fclean -C $(VISUDIR)
	@make fclean -C $(GENDIR)

re: fclean all

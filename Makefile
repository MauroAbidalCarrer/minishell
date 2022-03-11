NAME		=	minishell

SRCS		=	checker.c \
				main.c \
				signals/handle_signals.c \
				wildcard/match.c \
				wildcard/wild_it.c

_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix build/, $(_OBJS))

CC		=	cc
CFLAGS		=	-g3 -Wall -Werror -Wextra
INCLUDE		=	-I srcs/ -I srcs/execution -I ./srcs/libft -I ./srcs/signals \
				-I srcs/wildcard -I srcs/libdynamic_buffer/includes
LIBS		=	srcs/libdynamic_buffer/libdynamic_buffer.a srcs/libft/libft.a
LIBS_EXT	=	-lreadline


all		:	$(NAME)

build/%.o	:	srcs/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${CFLAGS} ${INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS) | libs
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBS_EXT) -o $(NAME)

libs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib);\
		make -C $$(dirname $$lib);\
	done

clean	:	
	rm -Rf build/

cleanlibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) clean;\
		make -C $$(dirname $$lib) clean;\
	done

cleanall	:	clean cleanlibs


fclean	:	clean
	rm -f ${NAME}

fcleanlibs	:
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) fclean;\
		make -C $$(dirname $$lib) fclean;\
	done

fcleanall	:	fclean fcleanlibs


re		:	fclean ${NAME}

relibs	:	
	@for lib in $(LIBS); do\
		echo make -C $$(dirname $$lib) re;\
		make -C $$(dirname $$lib) re;\
	done

reall	: relibs re


.PHONY	:	all libs clean cleanlibs cleanall fclean fcleanlibs fcleanall re relibs reall

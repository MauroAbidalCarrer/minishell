NAME		=	minishell

SRCS		=	builtins/echo.c \
				handle_signals.c \
				main.c

_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix build/, $(_OBJS))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
INCLUDE		=	-I includes/ -I ./srcs/libft
LIBS		=	srcs/libft/libft.a
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

NAME		=	minishell

SRCS		=	signals/handle_signals.c \
			checker/checker.c\
			checker/utils.c\
			execution/cmd_exe.c\
			execution/file_redirections.c\
			execution/high_level.c\
			execution/set_cmd.c\
			parsing_utils/utils2.c\
			parsing_utils/utils3.c\
			parsing_utils/utils.c\
			main.c

_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix build/, $(_OBJS))

CC		=	cc
CFLAGS		=	-g3 -Wall -Werror -Wextra
INCLUDE		=	-I srcs/\
			-I srcs/execution\
			-I ./srcs/signals\
			-I ./srcs/libft\
			-I ./srcs/checker\
			-I ./srcs/execution\
			-I ./srcs/parsing_utils
LIBS		=	srcs/libft/libft.a
LIBS_EXT	=	-lreadline


all		:	$(NAME)

build/%.o	:	srcs/%.c
	@if [ ! -d $(dir $@) ]; then\
		mkdir -p $(dir $@);\
	fi
	$(CC) ${CFLAGS} ${INCLUDE} -c $< -o $@

$(NAME)	:	$(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBS_EXT) -o $(NAME)

$(LIBS)	:	FORCE
	@for lib in $(LIBS); do\
		echo $(MAKE) -C $$(dirname $$lib);\
		$(MAKE) -C $$(dirname $$lib);\
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

.PHONY	:	all clean cleanlibs cleanall fclean fcleanlibs fcleanall re relibs reall FORCE

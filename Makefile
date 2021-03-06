NAME		=	minishell

SRCS		=	builtins/ms_cd.c \
				builtins/ms_echo.c \
				builtins/ms_env.c \
				builtins/ms_exit.c \
				builtins/ms_export.c \
				builtins/ms_export2.c \
				builtins/ms_pwd.c \
				builtins/ms_unset.c \
				builtins/quote_utils.c \
				checker/checker.c\
				checker/utils.c\
				execution/cmd_exe.c\
				execution/expand_all.c\
				execution/set_streams.c\
				execution/high_level.c\
				execution/set_cmd.c\
				execution/here_docs.c\
				get_next_line/get_next_line.c\
				get_next_line/util.c\
				get_next_line/get_next_line_utils.c\
				main.c\
				parsing_utils/env_utils.c\
				parsing_utils/utils.c\
				parsing_utils/utils2.c\
				parsing_utils/utils3.c\
				signals/handle_signals.c \
				variable_expansion/append_variables.c \
				variable_expansion/var_expand.c \
				variable_expansion/var_expand2.c \
				variable_expansion/var_expand3.c \
				variable_expansion/var_expand_in_heredoc.c \
				wildcard/get_sorted_files.c \
				wildcard/test_if_wildcard_ambiguous.c \
				wildcard/match.c \
				wildcard/wild_it.c \
				wildcard/wild_it2_it_is_back.c

_OBJS		=	${SRCS:.c=.o}
OBJS		=	$(addprefix build/, $(_OBJS))
DEPS		=	$(OBJS:%.o=%.d)


CC			=	cc
CFLAGS		=	-g3 -Wall -Werror -Wextra -MMD
INCLUDE		=	-I srcs/\
				-I srcs/execution\
				-I ./srcs/builtins\
				-I ./srcs/signals\
				-I ./srcs/libft\
				-I ./srcs/checker\
				-I ./srcs/execution\
				-I ./srcs/parsing_utils\
				-I ./srcs/get_next_line\
				-I ./srcs/variable_expansion\
				-I ./srcs/wildcard\
				-I ./srcs/libdynamic_buffer/includes

LIBS		=	srcs/libft/libft.a\
				srcs/libdynamic_buffer/libdynamic_buffer.a
LIBS_EXT	=	-lreadline


all		:	$(NAME)

-include $(DEPS)
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


bonus	:	$(NAME)

.PHONY	:	all clean cleanlibs cleanall fclean fcleanlibs fcleanall re relibs reall FORCE bonus

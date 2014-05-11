NAME=mynotsominishell
SRC=mynotsominishell.c get_term_cap.c init_caps.c init_terminal.c stand.c restore_terminal.c resize.c
LIBPATH=../lib
LIB=my
RM=rm -f
all:$(SRC)
	cc -L$(LIBPATH) -g $(SRC) -l$(LIB) -ltermcap -o $(NAME)
clean:
	-$(RM) $(NAME)
	-$(RM) *.o
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core
	-$(RM) *.swp
fclean:clean
re:fclean all

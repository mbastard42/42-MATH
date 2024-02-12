#	COMPILED LANGUAGES ] ===========================================================================	#
#	                                           [  CONFIG  ] ========================================	#
#	======================================================================================= [  LEAVE	#
#																										#
#	                                     [  NAME AND LOCATION  ] ===================================	#
BDIR	:=	bin/
NAME	:=	$(BDIR)computor
#	                                           [  FILES  ] =========================================	#
FILE	:=	cpp
SDIR	:=	src/
COMP	:=	o
ODIR	:=	.obj/
#	                                          [  COMPILER  ] =======================================	#
CC		:=	c++
CFLG	:=	-Wall -Wextra -Werror
LFLG	:=	
#																										#
#	============================================================================== [  MAKEFILE UTILS	#
#																										#
MAKEFLAGS	+=	--silent
RESET		:=	\033[0m
BOLD		:=	\033[1m
ITALIC		:=	\033[3m
GREY		:=	\033[90m
RED			:=	\e[0;31m
YELLOW		:=	\e[0;33m
GREEN		:=	\e[0;32m
#																										#
SRCS		:=	$(shell find $(SDIR) -name "*.$(FILE)")
OBJS		:=	$(subst $(SDIR),$(ODIR), ${SRCS:.$(FILE)=.$(COMP)})
#																										#
#	============================================================================== [  MAKEFILE RULES	#
#																										#
$(ODIR)%.$(COMP)	:	$(SDIR)%.$(FILE)
#																										#
	mkdir -p $(subst $(SDIR),$(ODIR), $(shell dirname $<)/)
	$(CC) $(CFLG) -c $< -o ${addprefix $(ODIR), ${<:$(SDIR)%.$(FILE)=%.$(COMP)}}
	echo "build\t\t$(YELLOW)compiled$(RESET)\t$(GREY)$(ODIR)${<:$(SDIR)%.$(FILE)=%.$(COMP)}$(RESET)"
#																										#
${NAME}				:	$(OBJS)
#																										#
	mkdir -p $(BDIR)
	$(CC) $(CFLG) $(LFLG) $(OBJS) -o $(NAME)
	echo "$(GREEN)build\t\tlinked\t\t$(BOLD)$(NAME)$(RESET)"
#																										#
print	:
#																										#
	echo "$(BOLD)RULE\t\tACTION\t\tTARGET$(RESET)"
#																										#
build	:	print ${NAME}
#																										#
clean	:	print
#																										#
	rm -rf $(ODIR)
	echo "$(GREY)clean$(RESET)\t\t$(RED)deleted$(RESET)\t\t$(ODIR)"
#																										#
fclean	:	print clean
#																										#
	rm -rf $(BDIR)
	echo "$(GREY)fclean$(RESET)\t\t$(RED)deleted$(RESET)\t\t$(BDIR)"
#																										#
re		:	print fclean build
#																										#
all		:	print build clean
#																										#
.PHONY	:	print build clean fclean re all
#																										#
#	                                       [  CUSTOM RULES  ] ======================================	#
#																										#
bonus	:	build																						#
#																										#
.PHONY	:	bonus
#																										#
#	===================================================================================== [ MAKEFILE	#

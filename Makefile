FILE				:=	c
MAKEFLAGS			+=	--silent

RESET				:=	\033[0m
BOLD				:=	\033[1m
ITALIC				:=	\033[3m
RED					:=	\e[0;31m
YELLOW				:=	\e[0;33m
GREEN				:=	\e[0;32m
GREY				:=	\033[90m

BDIR				:=	bin/
NAME				:=	$(BDIR)computor

SDIR				:=	src/
SRC					:=	$(shell find $(SDIR) -name "*.$(FILE)")

ODIR				:=	.obj/
OBJ					:=	$(subst $(SDIR),$(ODIR), ${SRC:.$(FILE)=.o})

CC					:=	gcc
CFLG				:=	-Wall -Wextra -Werror
LFLG				:=

$(ODIR)%.o			:	$(SDIR)%.$(FILE)

	mkdir -p $(subst $(SDIR),$(ODIR), $(shell dirname $<)/)
	$(CC) $(CFLG) -c $< -o ${addprefix $(ODIR), ${<:$(SDIR)%.$(FILE)=%.o}}
	echo "build\t\t$(YELLOW)compiled$(RESET)\t$(GREY)$(ODIR)${<:$(SDIR)%.$(FILE)=%.o}$(RESET)"
# 
help				:

	echo "$(BOLD)You can run the following commands:\n\
	- $(RESET)build:$(GREY)\tcompile $(NAME)\n\
	- $(RESET)bonus:$(GREY)\tcompile $(NAME) with bonus\n\
	- $(RESET)clean:$(GREY)\tdelete $(ODIR)\n\
	- $(RESET)fclean:$(GREY)\t$(ITALIC)clean$(RESET)$(GREY) and delete $(BDIR)\n\
	- $(RESET)re:$(GREY)\t\t$(ITALIC)fclean$(RESET)$(GREY) and $(ITALIC)build$(RESET)$(GREY)\n\
	- $(RESET)all:$(GREY)\t\t$(ITALIC)build$(RESET)$(GREY), $(ITALIC)test$(RESET)$(GREY) and $(ITALIC)clean$(RESET)$(GREY)"
#
${NAME}				:	$(OBJ)

	mkdir -p $(BDIR)
	$(CC) $(CFLG) $(LFLG) $(OBJ) -o $(NAME)
	echo "$(GREEN)build\t\tlinked\t\t$(BOLD)$(NAME)$(RESET)"
# 
info				:

	echo "$(BOLD)RULE\t\tACTION\t\tTARGET$(RESET)"
#
build				:	info ${NAME}
#
bonus				:	build
# 
clean				:	info

	rm -rf $(ODIR)
	echo "$(GREY)clean$(RESET)\t\t$(RED)deleted$(RESET)\t\t$(ODIR)"
# 
fclean				:	info clean

	rm -rf $(BDIR)
	echo "$(GREY)fclean$(RESET)\t\t$(RED)deleted$(RESET)\t\t$(BDIR)"
# 
re					:	info fclean build
# 
all					:	info build clean
# 
.PHONY				:	help info build bonus clean fclean re all
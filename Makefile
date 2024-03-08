NAME	=	life_game

SRCS	=	main.cpp

CPP		=	c++
CPPFLAG	=	-std=c++11
RM		=	rm -f
CP		=	cp tmp/main.cpp .

all		:
			@$(CPP) $(CPPFLAG) $(SRCS) -o $(NAME)

fclean	:
			@$(RM) $(NAME)

re		:
			@$(MAKE) fclean
			@$(MAKE) all

.PHONY: all fclean re

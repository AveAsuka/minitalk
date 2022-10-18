NAME_S		= 	./server 
NAME_C		= 	./client

SRCS		=	ft_putchar_fd.c alert.c \
				ft_strlen.c server_bonus.c ft_atoi.c \
				ft_putnbr_fd.c client_bonus.c \
			
OBJS		= ${SRCS:.c=.o}

SRCS_C		=	ft_putchar_fd.c alert.c \
				ft_strlen.c ft_atoi.c \
				ft_putnbr_fd.c client_bonus.c \
			
OBJS_C		= ${SRCS_C:.c=.o}

SRCS_S		=	ft_putchar_fd.c alert.c \
				ft_strlen.c server_bonus.c \
				ft_putnbr_fd.c \
			
OBJS_S		= ${SRCS_S:.c=.o}

CC			= cc
FLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
HEADER		= minitalk_bonus.h

all:	${OBJS} ${NAME_C} ${NAME_S}
bonus:	${OBJS} ${NAME_C} ${NAME_S}

${NAME_C}:	${OBJS_C}
			${CC} ${OBJS_C} -o ${NAME_C}
			
${NAME_S}:	${OBJS_S}
			${CC} ${OBJS_S} -o ${NAME_S}
					
${OBJS} : ${HEADER} Makefile

.c.o:	
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean:	
		${RM} ${OBJS}
		
fclean:	clean
		${RM} ${NAME_C} ${NAME_S}

re:		fclean all bonus

.PHONY:	all bonus clean fclean re

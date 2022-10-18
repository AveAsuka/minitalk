
#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_func
{
    int bol;     // 'сигнал-болванка', из которого делаем наш символ
    char sym;    // наш формируемый символ
    char *fin;   // наша финальная строка на вывод
    int z;       // количество символов 
}   t_func;

void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *str);
void	ft_putnbr_fd(int n, int fd);
void    alert(char *text, int pid);
int     ft_atoi(const char *str);

#endif

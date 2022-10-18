#include "minitalk_bonus.h"

// Функция, в которую отсылаем при любой ошибке - 1. Сигнал ошибки от сервера, 
// 2. Слишком долгий отклик от сервера, 3. Ошибка функции sigaction,
// 4. Ошибка функции kill, 5. Неккоректный ввод исходных данных в клиенте
void alert(char *text, int pid)
{
	int	i;

	i = 0;
	while (text[i])
		i++;
	write(1, text, i);
	write(1, "\n", 1);
	if (pid > 0)			
		kill(pid, SIGUSR2); 
	exit(EXIT_FAILURE);
}

#include "minitalk_bonus.h"

// Принимаем сигналы, 'расшифровываем' и копим их, 
// отправляем обратные сигналы, выводим.

// Короче тут мы берем переменную такого типа, потому что она 
// меняется в одну инструкцию, что препятствует расихрону
volatile sig_atomic_t	g_response[2] = {};

// Функция, которая выводит конечную строку.
static char *out_str(char *fin, int z)
{
    write(1, fin, z);
	write(1, "\n", 1);
	if (fin)
		free(fin);
	fin = NULL;
	return (NULL);
}

// Функция, которая принимает сформированный символ и добавляет к строке
// (на самом деле строка неэлегнтно пересоздается).
static char *send_symb(char *fin, char sym, int z)
{
    char *per; // 'пересадка' 
    int i;

    i = 0;
    
    if (sym == '\0')
        return(out_str(fin, z - 1));

    per = (char *)malloc(sizeof(char) * (z + 1));
    if (!per)
		alert("Ошибка в маллоке!", 0);
    if (z != 1)
    {
        while(fin[i])
        {
            per[i] = fin[i]; 
            i++;
        }
        if (fin)
            free(fin);
        fin = NULL;
    }
    per[i] = sym;
    per[++i] = '\0';
       
    return (per);
}

// Функция, которая вызывается при 'обработке сигнала',
// для SIGUSR1, который '1', и для SIGUSR2, который '0'.
static void sig_catch(int signum, siginfo_t *amber, void *context)
{
    static t_func	gubert;

    (void)context; // Сразу нулим третий ненужный параметр

    if (gubert.bol == 0)
    {
        gubert.bol = 128;
        gubert.sym = 0;
    }

    // Меняем наш 'сигнал-болванку' - типо нули когда надо меняем.
    if (signum == SIGUSR1)   // В клиенте мы его прописали как '1'.
    {
        gubert.sym = gubert.sym + gubert.bol;
        gubert.bol = gubert.bol >> 1;
    }
    else 
        gubert.bol = gubert.bol >> 1;

    if (gubert.bol == 0) // Когда приняли 8 сигналов болванка 'обнуляется'.
    {
        gubert.z++; // Счетчик символов в строке.
        gubert.fin = send_symb(gubert.fin, gubert.sym, gubert.z); // Подаем:
        // нашу строку на вывод, сам новый символ, общее их кол-во.
        if (gubert.sym == '\0') // Когда доходим до конца поданной строки,
            gubert.z = 0;       // то обнуляем счетчик.
    }
    g_response[1] = amber->si_pid; // обработчик сигнала закончил свою работу
	g_response[0] = 1;             // и после этого меняет флаг
}

// Тут мне надо расписать следующие:
// 1) выдача PID-а сервера;
// 2) постоянное "ожидание" посылания текста (pause);
// 3) настройка переопределения сигналов.
int main(void)
{   
    struct  sigaction amber;
    // 1)
    write(1, "Server PID: ", 12);
    ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);

// 3) Надо переопределить сигналы SIGUSR1 и SIGUSR2, посылаемые серверу:
// либо с помощью функции signal, либо sigaction.
    amber.sa_flags = SA_SIGINFO;            // Обработчик сигнала требует 3-х аргументов, а не одного. 
                             // В этом случае надо использовать параметр sa_sigaction вместо sa_handler. 
    amber.sa_sigaction = sig_catch; // "Привязка" структуры с нашим 'объектом' - функцией.

// Обработчик сигнала, который его переопределяет / дает новую задачу
// (функция sigaction возвращают 0 при удачном завершении работы функции и -1 при ошибке).
    if (sigaction(SIGUSR1, &amber, 0) == -1 || sigaction(SIGUSR2, &amber, 0) == -1)
        alert("Неккоректное переопределение сигнала!", 0); // 3.

    while (1) // 2) Ставим в вечное ожидание сигналов от клиента -
    {           //  и сразу тут меняем флаги и посылаем ответный сигнал.
		while (g_response[0] != 1)
		{
		}
		g_response[0] = 0;
		kill(g_response[1], SIGUSR1);
	}
}

// i++ - сначала выводит, потом прибавляет
// ++i - сначала прибавляет, потом выводит
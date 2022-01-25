#include "minishell.h"

//Вывод строки
void	ft_putstr(char *str, int std_var)
{
	int	i;

	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i])
		i++;
	write(std_var, str, i);
}

//Вывод ошибок с выходом из программы
void	ft_puterror(t_shell *shell, int code, char *name)
{
	ft_putstr(COLOR_RED, 2);
	ft_putstr("Error: ", 2);
	if (code == 1)
		ft_putstr("Programmu neobhodimo zapuskat bez parametrov\n", 2);
	if (code == 2)
	{
		ft_putstr("Ne udalos videlit pamyat. ", 2);
		ft_putstr(name, 2);
	}
	if (code == 3)
		ft_putstr("excve\n", 2);
	if (code == 4)
	{
		ft_putstr("incorrect variable. ", 2);
		ft_putstr(name, 2);
	}
	ft_putstr(COLOR_RESET, 2);
	ms_shell_destroy(shell);
	exit(1);
}

//Вывод ошибок без выхода из программы
void	ft_puterror_noexit(t_shell *shell, int code)
{
	ft_putstr(COLOR_RED, 2);
	ft_putstr("Error: ", 2);
	if (code == 1)
		ft_putstr("Ne udalos voyti v ukazannuyu directoriyu\n", 2);
	ft_putstr(COLOR_RESET, 2);
	shell->output_error = 1;
}

//Вывод сообщения о выходе
void	ft_putexit(t_shell *shell)
{
	ft_putstr(COLOR_GREEN, 1);
	if (OS_VERSION == 1)
		ft_putstr("Exit: Vi pokinuli programmu. Prihodite eshe!!!\n", 1);
	if (OS_VERSION == 2)
		ft_putstr("\nExit: Vi pokinuli programmu. Prihodite eshe!!!\n", 1);
	ft_putstr(COLOR_RESET, 1);
	ms_shell_destroy(shell);
	exit(0);
}
